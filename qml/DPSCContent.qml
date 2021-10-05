import QtQuick 2.0
import QtQuick.Layouts 1.3
import "dpscscripts.js" as PointSingleColumnScripts
import "dpscstatescripts.js" as PointStateScripts
Content {
    id: dpscBody
    signal requestControllerValues
    signal requestOrderedDartsInputs
    signal requestStatusFromBackend
    signal requestStart
    signal requestStop
    signal requestRestart
    onRequestRestart: PointSingleColumnScripts.handleRequestTournamentReset()
    signal requestUndo
    signal requestRedo
    signal sendInput(string json)
    signal setupGame
    signal requestPersistState
    readonly property QtObject metaValues: DartsMetaValues{}
    GridLayout{
        id: bodyLayout
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
            onRestartButtonClicked: PointSingleColumnScripts.handleRequestTournamentReset()
            onLeftButtonClicked: applicationInterface.requestUndo()
            onRightButtonClicked: applicationInterface.requestRedo()
        }
        DPSCBoard{
            id: singleColumnPointBoard
            Layout.fillWidth: true
            Layout.minimumWidth: dpscBody.width*0.75
            Layout.maximumWidth: dpscBody.width*0.75
            Layout.alignment: Qt.AlignHCenter
        }
        KeyDataDisplay{
            id: keyDataDisplay
            Layout.fillWidth: true
        }
        PointKeyPad{
            id: pointKeyPad
            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            onSendInput: PointSingleColumnScripts.handleScoreKeyPadInput(value,keyCode)
        }
    }
    states: [
        State {
            name: "winner"
            StateChangeScript{
                script: PointStateScripts.declareWinner()
            }
        },
        State {
            name: "stopped"
            StateChangeScript{
                script: PointStateScripts.backendIsStopped()
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
                script: PointStateScripts.backendProcessesInput()
            }
        },
        State {
            name: "waitingForInput"
            StateChangeScript{
                script: PointStateScripts.backendAwaitsInput()
            }
        }
    ]
    Component.onCompleted: PointSingleColumnScripts.initializeComponent()
    Component.onDestruction: PointSingleColumnScripts.disconnectInterface()
}
