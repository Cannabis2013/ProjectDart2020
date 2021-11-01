import QtQuick 2.0
import QtQuick.Layouts 1.3
import "dpscscripts.js" as DPSCScriptss
import "dpscstatescripts.js" as DPSCStateScripts
Content {
    id: dpscContent
    readonly property QtObject metaValues: DartsMetaValues{}
    GridLayout{
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        TurnController{
            id: pointSingleColumnTurnController
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.maximumHeight: 100
            Layout.alignment: Qt.AlignHCenter
            onStartButtonClicked: applicationInterface.requestStartGame()
            onResumeButtonClicked: applicationInterface.requestStartGame()
            onPauseButtonClicked: applicationInterface.requestStopGame()
            onRestartButtonClicked: DPSCScriptss.resetTournament()
            onLeftButtonClicked: applicationInterface.requestUndo()
            onRightButtonClicked: applicationInterface.requestRedo()
        }
        DPSCBoard{
            id: dpscScoreBoard
            Layout.minimumWidth: dpscContent.width*0.8
            Layout.maximumWidth: dpscContent.width*0.8
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
            onSendInput: DPSCScriptss.handleScoreKeyPadInput(value,keyCode)
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
    Component.onCompleted: DPSCScriptss.initializeComponent()
    Component.onDestruction: DPSCScriptss.disconnectInterface()
}
