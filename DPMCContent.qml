import QtQuick 2.0
import QtQuick.Layouts 1.3
import "dpmcscripts.js" as DartsPointMultiColumnScripts
Content {
    id: dartsPointMultiColumnBody
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
    readonly property QtObject metaValues: DartsMetaValues{}
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
        DPMCBoard{
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
                script: singleColumnTurnController.ready()
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
    Component.onDestruction: DartsPointMultiColumnScripts.disconnectInterface()
}
