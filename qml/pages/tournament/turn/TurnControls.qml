import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls
import "scripts.js" as Scripts

Item {
        id: turnRect

        signal undoClicked
        signal redoClicked
        signal restartClicked
        signal menuClicked

        function updateValues(canUndo, canRedo) {
                undoButton.enabled = canUndo
                redoButton.enabled = canRedo
        }

        GridLayout {
                anchors.fill: parent

                Button {
                        id: menuButton
                        flat: true
                        font.pointSize: 18
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: "Menu"
                        onClicked: menuClicked()
                }

                Button {
                        id: restartButton
                        flat: true
                        font.pointSize: 18
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: "Restart"
                        onClicked: restartClicked()
                }

                Button {
                        id: undoButton
                        flat: true
                        font.pointSize: 18
                        Layout.minimumWidth: 74
                        Layout.maximumWidth: 74
                        Layout.fillHeight: true
                        text: "Undo"
                        enabled: false
                        onClicked: undoClicked()
                }

                Button {
                        id: redoButton
                        flat: true
                        font.pointSize: 18
                        Layout.minimumWidth: 74
                        Layout.maximumWidth: 74
                        Layout.fillHeight: true
                        text: "Redo"
                        enabled: false
                        onClicked: redoClicked()
                }

                Item {
                        Layout.fillWidth: true
                }
        }
}
