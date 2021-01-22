import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
    id: body

    clip: true
    signal startButtonClicked
    signal leftButtonClicked
    signal rightButtonClicked

    signal startButtonPressAndHoldClicked
    signal leftButtonPressAndHoldClicked
    signal rightButtonPressAndHoldClicked

    property bool startButtonEnablePressAndHold : false
    onStartButtonEnablePressAndHoldChanged: startButtonComponent.enablePressAndHold(startButtonEnablePressAndHold)

    property string startButtonText: "Start"
    onStartButtonTextChanged: startButtonComponent.startButtonText = startButtonText

    property bool startButtonEnabled: false
    onStartButtonEnabledChanged: startButtonComponent.startButtonEnabled = startButtonEnabled

    property int currentRoundIndex: 0
    property string currentPlayer: ""

    onCurrentRoundIndexChanged: currentRoundLabel.text = currentRoundIndex
    onCurrentPlayerChanged: currentPlayerLabel.text = currentPlayer

    property bool undoButtonEnabled: false
    onUndoButtonEnabledChanged: leftButton.enabled = undoButtonEnabled
    property bool redoButtonEnabled: false
    onRedoButtonEnabledChanged: rightButton.enabled = redoButtonEnabled

    function updateState(roundIndex, playerName, undoPossible, redoPossible)
    {
        currentRoundIndex  = roundIndex;
        body.currentPlayer = playerName;
        leftButton.enabled = undoPossible;
        rightButton.enabled = redoPossible;
    }

    QtObject{
        id: textBeholder
        property string currentRoundText: qsTr("Current round: ")
        property string currentPlayerText: qsTr("Current player: ")
    }

    GridLayout{
        anchors.fill: parent
        flow: GridLayout.LeftToRight
        Layout.fillHeight: true
        Layout.fillWidth: true

        StartButtonComponent {
            id: startButtonComponent
            Layout.fillHeight: true
            Layout.preferredWidth: 64
            onPressAndHoldClicked: startButtonPressAndHoldClicked()
            startButtonText: body.startButtonText
            onStartButtonClicked: body.startButtonClicked()
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
                text: "" + currentRoundIndex
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
            onPressAndHoldClicked: rightButtonPressAndHoldClicked()
            onClicked: rightButtonClicked()
            Layout.alignment: Qt.AlignVCenter
            enabled: false
        }
    }
}
