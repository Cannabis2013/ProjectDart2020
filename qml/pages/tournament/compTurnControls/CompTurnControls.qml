import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Item {
        id: turnRect
        clip: true

        signal undoClicked
        signal redoClicked
        signal restartClicked

        function update() {
                undoButton.active = dartsTurns.canUndo()
                redoButton.active = dartsTurns.canRedo()
        }

        GridLayout {
                anchors.fill: parent

                Button {
                        text: "Menu"
                        height: parent.height
                        Layout.fillHeight: true
                        Layout.preferredWidth: 80
                        font.pointSize: 12
                        onClicked: menuRequest()
                }

                Item {
                        Layout.fillWidth: true
                }

                Button {
                        id: restartButton
                        text: "Restart"
                        Layout.preferredWidth: 96
                        Layout.fillHeight: true
                        onClicked: restartClicked()
                }

                ButtonControl {
                        id: undoButton
                        active: false
                        Layout.preferredWidth: 38
                        Layout.fillHeight: true
                        iconSource: "qrc:/pictures/Ressources/Pictures/undo.png"
                        onButtonClicked: undoClicked()
                }

                ButtonControl {
                        id: redoButton
                        active: false
                        Layout.fillHeight: true
                        Layout.preferredWidth: 38
                        iconSource: "qrc:/pictures/Ressources/Pictures/redo.png"
                        onButtonClicked: redoClicked()
                }
        }
}
