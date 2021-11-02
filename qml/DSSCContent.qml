import QtQuick 2.0
import QtQuick.Layouts 1.3
import "dsscscripts.js" as DartsScoresScripts
import "dsscstatescripts.js" as StateScripts
Content {
    id: dsscContent
    preferedPageTitle: "Darts 2021"
    DartsMetaValues{
        id: dartsMetaValues
    }
    GridLayout{
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
            Layout.alignment: Qt.AlignHCenter
            Layout.minimumWidth: dsscContent.width*0.8
            Layout.maximumWidth: dsscContent.width*0.8
        }
        KeyDataDisplay{
            id: keyDataDisplay
            Layout.fillWidth: true
        }
        DSSCKeyPad{
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
