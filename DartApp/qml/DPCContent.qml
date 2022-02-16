import QtQuick 2.0
import QtQuick.Layouts 1.3
import "dpscscripts.js" as DPSCScripts
import "dpscstatescripts.js" as DPSCStateScripts
Content {
    id: dpcContent
    preferedPageTitle: "Dart 2021"
    GridLayout{
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        TurnController{
            id: pointSingleColumnTurnController
            Layout.fillWidth: true
            Layout.minimumHeight: 48
            Layout.maximumHeight: 48
            Layout.alignment: Qt.AlignHCenter
            onStart: DPSCScripts.startGame()
            onPause: dpcContent.state = "stopped"
            onResume: dpcContent.state = "waitingForInput"
            onRestart: DPSCScripts.resetTournament()
            onUndo: DPSCScripts.undoClicked()
            onRedo: DPSCScripts.redoClicked()
        }
        DPSCBoard{
            id: dpscScoreBoard
            Layout.minimumWidth: dpcContent.width*0.8
            Layout.maximumWidth: dpcContent.width*0.8
            Layout.alignment: Qt.AlignHCenter
        }
        KeyDataDisplay{
            id: keyDataDisplay
            Layout.fillWidth: true
        }
        DPSCKeyPad{
            id: pointKeyPad
            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            onSendInput: DPSCScripts.handleScoreKeyPadInput(value,keyCode)
        }
    }
    states: [
        State {
            name: "winner"
            StateChangeScript{
                script: DPSCStateScripts.declareWinner()
            }
        },
        State {
            name: "stopped"
            StateChangeScript{
                script: DPSCStateScripts.backendIsStopped()
            }
        },
        State {
            name: "ready"
            StateChangeScript{
                script: pointSingleColumnTurnController.ready()
            }
        },
        State {
            name: "waitingForInputConfirmation"
            StateChangeScript{
                script: DPSCStateScripts.backendProcessesInput()
            }
        },
        State {
            name: "waitingForInput"
            StateChangeScript{
                script: DPSCStateScripts.backendAwaitsInput()
            }
        }
    ]
    Component.onCompleted: DPSCScripts.init()
}
