import QtQuick 2.0
import QtQuick.Layouts 1.3

import "dartsmultiattemptscripts.js" as MultiAttemptScripts
import "multiattemptstatescripts.js" as StateScripts

/*
  Gamemodes:
    FirstToPost = 0x1,
    RoundLimit =0x2,
    Circular = 0x3,
    Cricket = 0xAA
  */
Content {
    id: dartsMultiAttemptBody
    signal requestControllerValues
    signal requestMultiAttemptScores
    signal requestStatusFromBackend
    signal requestStart
    signal requestStop
    signal requestRestart
    onRequestRestart: MultiAttemptScripts.handleRequestTournamentReset()
    signal requestUndo
    signal requestRedo
    signal sendInput(string json)
    signal setupGame
    signal requestPersistState
    /*
      Tournament metadata property
      */
    QtObject{
        id: dartsMultiAttemptValues
        property string title: ""
        property int keyPoint: 501
        property int attempts: 3
        property string winnerName: ""
        property var assignedPlayerNames: []
    }

    GridLayout{
        id: bodyLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        TurnController{
            id: multiAttemptScoreTurnController
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.maximumHeight: 100
            Layout.alignment: Qt.AlignHCenter
            onStartButtonClicked: requestStart()
            onResumeButtonClicked: requestStart()
            onPauseButtonClicked: requestStop()
            onRestartButtonClicked: requestRestart()
            onLeftButtonClicked: MultiAttemptScripts.undoClicked()
            onRightButtonClicked: MultiAttemptScripts.redoClicked()
        }
        MultiAttemptScoreScoreBoard{
            id: multiAttemptScoreBoard
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 160

        }
        MyRectangle{
            Layout.fillHeight: true
        }

        KeyDataDisplay{
            id: keyDataDisplay
            Layout.fillWidth: true
            Layout.maximumHeight: 40
            visible: status === Loader.Ready
        }
        Rectangle{
             color: "transparent"
             height: 5
        }
        ScoreKeyPad{
            id: scoreKeyPad
            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumHeight: 384
            Layout.minimumHeight: 128
        }
    }
    states: [
        State {
            name: "winner"
            StateChangeScript{
                script: StateScripts.declareWinner()
            }
        },
        State {
            name: "stopped"
            StateChangeScript{
                script: StateScripts.backendIsStopped()
            }
        },
        State {
            name: "ready"
            StateChangeScript{
                script: multiAttemptScoreTurnController.backendIsReady()
            }
        },
        State {
            name: "waitingForInputConfirmation"
            StateChangeScript{
                script: StateScripts.backendProcessesInput()
            }
        },
        State {
            name: "waitingForInput"
            StateChangeScript{
                script: StateScripts.backendAwaitsInput()
            }
        }
    ]
    Component.onCompleted: MultiAttemptScripts.initializeComponent()
    Component.onDestruction: MultiAttemptScripts.disconnectInterface()
}
