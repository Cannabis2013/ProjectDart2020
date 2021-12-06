import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
TurnControllerInterface {
    id: turnControllerBody
    onReset: state = "initialState"
    onReady: state = "startState"
    onBackendAwaitsInput: state = "runningState"
    onBackendProcessesInput: state = "waitState"
    onBackendIsStopped: state = "stoppedState"
    onBackendHasDeclaredAWinner: state = "restartState"
    onStartButtonEnablePressAndHoldChanged: startButtonComponent.pressAndHoldEnabled = startButtonEnablePressAndHold
    onCurrentRoundIndexChanged: navView.currentRoundIndex = currentRoundIndex
    onCurrentPlayerChanged: navView.currentPlayerName = currentPlayer
    onLeftButtonEnabledChanged: navView.enableUndo(leftButtonEnabled)
    onRightButtonEnabledChanged: navView.enableRedo(rightButtonEnabled)
    GridLayout{
        flow: GridLayout.LeftToRight
        anchors.fill: parent
        StartButtonsView {
            id: startButtonComponent
            Layout.fillHeight: true
            Layout.minimumWidth: 64
            Layout.maximumWidth: 64
            onResumeButtonClicked: turnControllerBody.resume()
            onPauseButtonClicked: turnControllerBody.pause();
            onStartButtonClicked: turnControllerBody.start()
            onRestartButtonClicked: turnControllerBody.restart()
        }
        NavigationView{
            id: navView
            Layout.fillWidth: true
            Layout.minimumHeight: 40
            Layout.maximumHeight: 40
            Layout.alignment: Qt.AlignVCenter
            Layout.leftMargin: 12
            Layout.rightMargin: 12
            onUndoClicked: undo()
            onRedoClicked: redo()
        }
    }
    states: [
        State {
            name: "initialState"
            PropertyChanges {
                target: startButtonComponent
                startButtonVisible: true
                startButtonEnabled: false

            }
            StateChangeScript{
                script: navView.reset()
            }
        },
        State {
            name: "startState"
            PropertyChanges {
                target: startButtonComponent
                startButtonVisible: true
                startButtonEnabled: true
                restartButtonEnabled: false
            }
            StateChangeScript{
                script: {
                    navView.enableUndo(false);
                    navView.enableRedo(false);
                }
            }
        },
        State {
            name: "runningState"
            PropertyChanges {
                target: startButtonComponent
                startButtonVisible : false
                pauseButtonVisible: true
            }
            StateChangeScript{
                script: {
                    navView.enableUndo(turnControllerBody.leftButtonEnabled);
                    navView.enableRedo(turnControllerBody.rightButtonEnabled);
                }
            }
        },
        State {
            name: "waitState"
            PropertyChanges {
                target: startButtonComponent
                waitButtonVisible: true
            }
            StateChangeScript{
                script: {
                    navView.enableUndo(false);
                    navView.enableRedo(false);
                }
            }
        },
        State {
            name: "stoppedState"
            PropertyChanges {
                target: startButtonComponent
                resumeButtonVisible: true
                pauseButtonVisible : false
                startButtonVisible : false
            }
            StateChangeScript{
                script: {
                    navView.enableUndo(false);
                    navView.enableRedo(false);
                }
            }
        },
        State {
            name: "restartState"
            PropertyChanges {
                target: startButtonComponent
                restartButtonVisible: true
            }
            StateChangeScript{
                script: {
                    navView.enableUndo(false);
                    navView.enableRedo(false);
                }
            }
        }
    ]
}
