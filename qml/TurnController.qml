import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

import "turnControllerScripts.js" as TurnControllerScripts

Item {
    id: turnControllerBody
    clip: true
    // Buttons
    signal startButtonClicked
    signal pauseButtonClicked
    signal resumeButtonClicked
    signal restartButtonClicked
    signal leftButtonClicked
    signal rightButtonClicked
    // Signal backend states
    signal reset
    onReset: state = "initialState"
    signal ready
    onReady: state = "startState"
    signal backendAwaitsInput
    onBackendAwaitsInput: state = "runningState"
    signal backendProcessesInput
    onBackendProcessesInput: state = "waitState"
    signal backendIsStopped
    onBackendIsStopped: state = "stoppedState"
    signal backendHasDeclaredAWinner
    onBackendHasDeclaredAWinner: state = "restartState"
    signal leftButtonPressAndHoldClicked
    signal rightButtonPressAndHoldClicked

    property bool startButtonEnablePressAndHold : true
    onStartButtonEnablePressAndHoldChanged: startButtonComponent.pressAndHoldEnabled = startButtonEnablePressAndHold

    property string currentRoundIndex: initialTextBoxValues.roundText
    onCurrentRoundIndexChanged: turnControllerView.currentRoundIndex = currentRoundIndex
    property string currentPlayer: initialTextBoxValues.playerText
    onCurrentPlayerChanged: turnControllerView.currentPlayer = currentPlayer
    property bool leftButtonEnabled: false
    onLeftButtonEnabledChanged: leftButton.enabled = leftButtonEnabled
    property bool rightButtonEnabled: false
    onRightButtonEnabledChanged: rightButton.enabled = rightButtonEnabled
    QtObject{
        id: textBeholder
        property string currentRoundText: qsTr("Current round: ")
        property string currentPlayerText: qsTr("Current player: ")
    }
    QtObject{
        id: initialTextBoxValues
        readonly property string roundText: "Current round"
        readonly property string playerText: "Current player"
    }
    GridLayout{
        flow: GridLayout.LeftToRight
        anchors.fill: parent
        StartButtonComponent {
            id: startButtonComponent
            Layout.fillHeight: true
            width: 64
            onResumeButtonClicked: turnControllerBody.resumeButtonClicked()
            onPauseButtonClicked: turnControllerBody.pauseButtonClicked();
            onStartButtonClicked: turnControllerBody.startButtonClicked()
            onRestartButtonClicked: TurnControllerScripts.setRestart()
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
        DartsTurnControllerView {
            id: turnControllerView
            Layout.fillHeight: true
            Layout.fillWidth: true
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
                textDescriptionVisible : true
                startButtonVisible: true
                startButtonEnabled: false
            }
            StateChangeScript{
                script: TurnControllerScripts.clearLabels()
            }
        },
        State {
            name: "startState"
            PropertyChanges {
                target: startButtonComponent
                textDescriptionVisible: false
                startButtonVisible: true
                startButtonEnabled: true
            }
        },
        State {
            name: "runningState"
            PropertyChanges {
                target: startButtonComponent
                startButtonVisible : false
                pauseButtonVisible: true
                textDescriptionVisible: true
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
                textDescriptionVisible : true
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
                textDescriptionVisible: false
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
                text: turnControllerView.currentRoundIndex
            }
            PropertyChanges {
                target: currentPlayerLabel
                text: turnControllerView.currentPlayer
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
