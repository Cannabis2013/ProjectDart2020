import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
        id: turnRect

        signal undoClicked
        signal redoClicked
        signal restartClicked

        function update() {
                undoButton.enabled = dartsTurns.canUndo()
                redoButton.enabled = dartsTurns.canRedo()
        }

        GridLayout {
                anchors.fill: parent

                Button {
                        text: "Menu"
                        height: parent.height
                        Layout.fillHeight: true
                        Layout.preferredWidth: 90
                        flat: true
                        font.pointSize: 18
                        onClicked: menuRequest()
                }

                Item {
                        Layout.fillWidth: true
                }

                Button {
                        id: restartButton
                        flat: true
                        font.pointSize: 18
                        Layout.fillHeight: true
                        text: "Restart"
                        onClicked: restartClicked()
                }

                Button {
                        id: undoButton
                        flat: true
                        font.pointSize: 18
                        Layout.fillHeight: true
                        text: "Undo"
                        enabled: false
                        onClicked: undoClicked()
                }

                Button {
                        id: redoButton
                        flat: true
                        font.pointSize: 18
                        Layout.fillHeight: true
                        text: "Redo"
                        enabled: false
                        onClicked: redoClicked()
                }
        }
}
