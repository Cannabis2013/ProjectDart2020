import QtQuick 2.0
import QtQuick.Layouts 1.3

import "dsscscripts.js" as DartsScoresScripts
import "dsscstatescripts.js" as StateScripts

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
    DartsMetaValues{
        id: dartsMetaValues
    }
    GridLayout{
        id: bodyLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        TurnController{
            id: singleColumnScoreTurnController
            Layout.fillWidth: true
            Layout.minimumHeight: 80
            Layout.maximumHeight: 80
            Layout.alignment: Qt.AlignHCenter
            onStartButtonClicked: applicationInterface.requestStartGame()
            onResumeButtonClicked: applicationInterface.requestStartGame()
            onPauseButtonClicked: applicationInterface.requestStopGame()
            onRestartButtonClicked: DartsScoresScripts.resetTournament()
            onLeftButtonClicked: DartsScoresScripts.undoClicked()
            onRightButtonClicked: DartsScoresScripts.redoClicked()
        }
        DSSCBoard{
            id: singleColumnScoreBoard
            Layout.fillWidth: true
            Layout.minimumWidth: dartsScoreSingleColumnBody.width*0.75
            Layout.maximumWidth: dartsScoreSingleColumnBody.width*0.75
            Layout.alignment: Qt.AlignHCenter
        }
        KeyDataDisplay{
            id: keyDataDisplay
            Layout.fillWidth: true
        }
        ScoreKeyPad{
            id: scoreKeyPad
            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
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
