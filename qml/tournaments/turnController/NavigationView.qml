import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../../buttons"

Item {
        id: controllerNavView
        signal enableUndo(bool val)
        onEnableUndo: leftButton.enabled = val
        signal enableRedo(bool val)
        onEnableRedo: rightButton.enabled = val
        signal undoClicked
        signal redoClicked
        signal reset
        onReset: playerDisplay.text = "Player (round)"
        property string currentRoundIndex: ""
        onCurrentRoundIndexChanged: playerDisplay.text = createPlayerString()
        property string currentPlayerName: ""
        onCurrentPlayerNameChanged: playerDisplay.text = createPlayerString()
        function createPlayerString() {
                var player = currentPlayerName
                var round = currentRoundIndex
                var string = `${player} (${round})`
                if (string !== "")
                        return string
                return "Player (round)"
        }
        GridLayout {
                anchors.fill: parent
                PushButton {
                        id: leftButton
                        width: 40
                        height: 40
                        image: "qrc:/pictures/Ressources/arrow.png"
                        backgroundColor: ThemeContext.navButtonsBackgroundColor
                        onClicked: undoClicked()
                        imageRotation: 180
                        imageMargins: 12
                        buttonRadius: 45
                        hoverEnabled: false
                        Layout.alignment: Qt.AlignVCenter
                        enabled: false
                        visible: true
                }
                ControllerPlayerDisplay {
                        id: playerDisplay
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        text: "Player (round)"
                }
                PushButton {
                        id: rightButton
                        width: 40
                        height: 40
                        image: "qrc:/pictures/Ressources/arrow.png"
                        backgroundColor: ThemeContext.navButtonsBackgroundColor
                        imageMargins: 12
                        buttonRadius: 45
                        hoverEnabled: false
                        onClicked: redoClicked()
                        Layout.alignment: Qt.AlignVCenter
                        enabled: false
                }
        }
}
