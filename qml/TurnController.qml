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
    onCurrentRoundIndexChanged: playerDisplay.text = createPlayerString()
    onCurrentPlayerChanged: playerDisplay.text = createPlayerString()
    onLeftButtonEnabledChanged: leftButton.enabled = leftButtonEnabled
    onRightButtonEnabledChanged: rightButton.enabled = rightButtonEnabled
    GridLayout{
        flow: GridLayout.LeftToRight
        anchors.fill: parent
        StartButtonComponent {
            id: startButtonComponent
            Layout.fillHeight: true
            Layout.minimumWidth: 64
            Layout.maximumWidth: 64
            onResumeButtonClicked: turnControllerBody.resumeButtonClicked()
            onPauseButtonClicked: turnControllerBody.pauseButtonClicked();
            onStartButtonClicked: turnControllerBody.startButtonClicked()
            onRestartButtonClicked: turnControllerBody.restartButtonClicked()
            onPressAndHoldClicked: turnControllerBody.state = "optionsState";
        }
        PushButton{
            id: leftButton
            width: 48
            height: 48
            image: "qrc:/pictures/Ressources/arrow.png"
            backgroundColor: ThemeContext.navButtonsBackgroundColor
            onClicked: leftButtonClicked()
            onPressAndHoldClicked: leftButtonPressAndHoldClicked()
            imageRotation: 180
            imageMargins: 20
            buttonRadius: 45
            hoverEnabled: false
            Layout.alignment: Qt.AlignVCenter
            enabled: false;
        }
        ControllerPlayerDisplay {
            id: playerDisplay
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Player (round)"
        }
        PushButton{
            id: rightButton
            width: 48
            height: 48
            image: "qrc:/pictures/Ressources/arrow.png"
            backgroundColor: ThemeContext.navButtonsBackgroundColor
            imageMargins: 20
            buttonRadius: 45
            hoverEnabled: false
            onClicked: rightButtonClicked()
            Layout.alignment: Qt.AlignVCenter
            enabled: false
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
                script: playerDisplay.text = "Player (round)"
            }
        },
        State {
            name: "startState"
            PropertyChanges {
                target: startButtonComponent
                startButtonVisible: true
                startButtonEnabled: true
            }
            PropertyChanges {
                target: leftButton
                enabled: false

            }
            PropertyChanges {
                target: rightButton
                enabled: false
            }
        },
        State {
            name: "runningState"
            PropertyChanges {
                target: startButtonComponent
                startButtonVisible : false
                pauseButtonVisible: true
            }
            PropertyChanges {
                target: leftButton
                enabled: turnControllerBody.leftButtonEnabled
            }
            PropertyChanges {
                target: rightButton
                enabled: turnControllerBody.rightButtonEnabled
            }
        },
        State {
            name: "waitState"
            PropertyChanges {
                target: startButtonComponent
                waitButtonVisible: true
            }
            PropertyChanges {
                target: leftButton
                enabled: false
            }
            PropertyChanges {
                target: rightButton
                enabled: false
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
            PropertyChanges {
                target: leftButton
                enabled: false
            }
            PropertyChanges {
                target: rightButton
                enabled: false
            }
        },
        State {
            name: "optionsState"
            PropertyChanges {
                target: startButtonComponent
                restartButtonVisible: true
                startButtonVisible: startButtonVisible
                pauseButtonVisible: pauseButtonVisible
                resumeButtonVisible: resumeButtonVisible
                startButtonEnabled: true
            }
            PropertyChanges {
                target: leftButton
                enabled: leftButton.enabled
            }
            PropertyChanges {
                target: rightButton
                enabled: rightButton.enabled
            }
        },
        State {
            name: "restartState"
            PropertyChanges {
                target: startButtonComponent
                restartButtonVisible: true
            }
            PropertyChanges {
                target: currentRoundLabel
                text: playerDisplay.currentRoundIndex
            }
            PropertyChanges {
                target: currentPlayerLabel
                text: playerDisplay.currentPlayer
            }
            PropertyChanges {
                target: leftButton
                enabled: false
            }
            PropertyChanges {
                target: rightButton
                enabled: false
            }
        }
    ]
}
