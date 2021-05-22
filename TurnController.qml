import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

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
    signal backendIsReady
    onBackendIsReady: state = "startState"
    signal backendAwaitsInput
    onBackendAwaitsInput: state = "runningState"
    signal backendProcessesInput
    onBackendProcessesInput: state = "waitState"
    signal backendIsStopped
    onBackendIsStopped: state = "stoppedState"
    signal backendHasDeclaredAWinner()
    onBackendHasDeclaredAWinner: state = "restartState"
    signal leftButtonPressAndHoldClicked
    signal rightButtonPressAndHoldClicked

    property bool startButtonEnablePressAndHold : true
    onStartButtonEnablePressAndHoldChanged: startButtonComponent.pressAndHoldEnabled = startButtonEnablePressAndHold

    property int currentRoundIndex: 0
    onCurrentRoundIndexChanged: currentRoundLabel.text = currentRoundIndex
    property string currentPlayer: ""
    onCurrentPlayerChanged: currentPlayerLabel.text = currentPlayer
    property bool leftButtonEnabled: false
    onLeftButtonEnabledChanged: leftButton.enabled = leftButtonEnabled
    property bool rightButtonEnabled: false
    onRightButtonEnabledChanged: rightButton.enabled = rightButtonEnabled
    QtObject{
        id: textBeholder
        property string currentRoundText: qsTr("Current round: ")
        property string currentPlayerText: qsTr("Current player: ")
    }

    GridLayout{
        flow: GridLayout.LeftToRight
        anchors.fill: parent
        StartButtonComponent {
            id: startButtonComponent
            Layout.fillHeight: true
            Layout.preferredWidth: 64
            onResumeButtonClicked: turnControllerBody.resumeButtonClicked()
            onPauseButtonClicked: turnControllerBody.pauseButtonClicked()
            onStartButtonClicked: turnControllerBody.startButtonClicked()
            onRestartButtonClicked: {
                turnControllerBody.state = "startState";
                turnControllerBody.restartButtonClicked();
            }
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

        GridLayout{
            Layout.fillWidth: true
            Layout.fillHeight: true

            flow: GridLayout.TopToBottom

            Label{
                id: currentRoundLabel
                color: ThemeContext.navTextDisplayColor
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: currentRoundIndex
                font.pointSize: 24
                verticalAlignment: Text.AlignBottom
                horizontalAlignment: Text.AlignHCenter
            }

            Label{
                id: currentPlayerLabel
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "white"
                text: currentPlayer
                font.pointSize: 24
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignHCenter
            }
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
        },
        State {
            name: "startState"
            PropertyChanges {
                target: startButtonComponent
                startButtonVisible: true
                startButtonEnabled: true
            }
        },
        State {
            name: "runningState"
            PropertyChanges {
                target: startButtonComponent
                textDescriptionVisible: true
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
                textDescriptionVisible: true
                restartButtonVisible: true
                startButtonVisible: startButtonVisible
                pauseButtonVisible: pauseButtonVisible
                resumeButtonVisible: resumeButtonVisible
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
                text: turnControllerBody.currentRoundIndex
            }
            PropertyChanges {
                target: currentPlayerLabel
                text: turnControllerBody.currentPlayer
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
    Component.onCompleted: state = "initialState"
}
