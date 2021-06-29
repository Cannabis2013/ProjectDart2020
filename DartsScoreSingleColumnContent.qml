import QtQuick 2.0
import QtQuick.Layouts 1.3

import "dartsscoresinglecolumnscripts.js" as DartsScoresScripts
import "multiattemptstatescripts.js" as StateScripts

Content {
    id: dartsScoreSingleColumnBody
    signal requestControllerValues
    signal requestMultiAttemptScores
    signal requestStatusFromBackend
    signal requestStart
    signal requestStop
    signal requestRestart
    onRequestRestart: DartsScoresScripts.handleRequestTournamentReset()
    signal requestUndo
    signal requestRedo
    signal sendInput(string json)
    signal setupGame
    signal requestPersistState
    /*
      Tournament metadata property
      */
    QtObject{
        id: dartsMetaValues
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
            id: singleColumnScoreTurnController
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.maximumHeight: 100
            Layout.alignment: Qt.AlignHCenter
            onStartButtonClicked: applicationInterface.requestStartGame()
            onResumeButtonClicked: applicationInterface.requestStartGame()
            onPauseButtonClicked: applicationInterface.requestStopGame()
            onRestartButtonClicked: DartsScoresScripts.resetTournament()
            onLeftButtonClicked: DartsScoresScripts.undoClicked()
            onRightButtonClicked: DartsScoresScripts.redoClicked()
        }
        DartsScoreSingleColumnBoard{
            id: singleColumnScoreBoard
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
                script: singleColumnScoreTurnController.ready()
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
    Component.onCompleted: DartsScoresScripts.initializeComponent()
    Component.onDestruction: DartsScoresScripts.disconnectInterface()
}
