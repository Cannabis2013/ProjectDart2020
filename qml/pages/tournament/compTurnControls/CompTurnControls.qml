import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "compTurnControls.js" as Scripts

Item {
        id: turnRect

        signal undoClicked
        signal redoClicked
        signal restartClicked

        function updateValues(jsonReport) {
                const turnInfo = jsonReport.turnInfo
                undoButton.enabled = turnInfo.canUndo
                redoButton.enabled = turnInfo.canRedo
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
