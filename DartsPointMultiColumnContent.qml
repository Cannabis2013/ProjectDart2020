import QtQuick 2.0
import QtQuick.Layouts 1.3

import "dartsPointMultiColumnScripts.js" as DartsPointMultiColumnScripts

/*
  Gamemodes:
    FirstToPost = 0x1,
    RoundLimit =0x2,
    Circular = 0x3,
    Cricket = 0xAA
  */
Content {
    id: dartsPointMultiColumnBody
    QtObject{
        id: textSourceContainer
        property string throwSuggestLabel: "Target row:"
        property string winnerLabel: "Winner:"
    }
    signal requestControllerValues
    signal requestSingleAttemptPoints
    signal requestStatusFromBackend
    signal requestStart
    signal requestStop
    signal requestRestart
    onRequestRestart: DartsPointMultiColumnScripts.handleRequestTournamentReset()
    signal requestUndo
    signal requestRedo
    signal sendInput(string json)
    signal setupGame
    signal requestPersistState
    /*
      Tournament metadata property
      */
    QtObject{
        id: dartsSingleAttemptValues
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
            id: singleColumnTurnController
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.maximumHeight: 100
            Layout.alignment: Qt.AlignHCenter
            onStartButtonClicked: applicationInterface.requestStartGame()
            onResumeButtonClicked: applicationInterface.requestStartGame()
            onPauseButtonClicked: applicationInterface.requestStopGame()
            onRestartButtonClicked: DartsPointMultiColumnScripts.handleRequestTournamentReset()
            onLeftButtonClicked: applicationInterface.requestUndo()
            onRightButtonClicked: applicationInterface.requestRedo()
        }
        DartsPointScoreBoard{
            id: pointScoreBoard
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
        }
        Rectangle{
             color: "transparent"
             height: 5
        }
        PointKeyPad{
            id: pointKeyPad
            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.maximumHeight: 384
            Layout.minimumHeight: 128
            onSendInput: DartsPointMultiColumnScripts.handlePointKeyPadInput(value,keyCode)
        }
    }
    states: [
        State {
            name: "winner"
            StateChangeScript{
                script: {
                    singleColumnTurnController.backendHasDeclaredAWinner();
                    pointKeyPad.enableKeyPad(false);
                    DartsPointMultiColumnScripts.setWinnerText();
                }
            }
        },
        State {
            name: "stopped"
            StateChangeScript{
                script: {
                    singleColumnTurnController.backendIsStopped();
                    pointKeyPad.enableKeyPad(false);
                }
            }
        },
        State {
            name: "ready"
            StateChangeScript{
                script: singleColumnTurnController.backendIsReady()
            }
        },
        State {
            name: "waitingForInputConfirmation"
            StateChangeScript{
                script: {
                    singleColumnTurnController.backendProcessesInput();
                    pointKeyPad.enableKeyPad(false);
                }
            }
        },
        State {
            name: "waitingForInput"
            StateChangeScript{
                script: {
                    singleColumnTurnController.backendAwaitsInput();
                    pointKeyPad.enableKeyPad(true);
                }
            }
        }
    ]
    Component.onCompleted: DartsPointMultiColumnScripts.initializeComponent()
    Component.onDestruction: DartsPointMultiColumnScripts.disconnectInterface();
}
