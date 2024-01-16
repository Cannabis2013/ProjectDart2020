import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "turnControlsSection.js" as Scripts

Item {
        id: turnRect

        signal undoClicked
        signal redoClicked
        signal restartClicked

        function updateValues(canUndo, canRedo) {
                undoButton.enabled = canUndo
                redoButton.enabled = canRedo
        }

        Row {
                anchors.fill: parent

                Button {
                        id: restartButton
                        flat: true
                        font.pointSize: 18
                        width: 90
                        height: parent.height
                        text: "Restart"
                        onClicked: restartClicked()
                }

                Button {
                        id: undoButton
                        flat: true
                        font.pointSize: 18
                        width: 74
                        height: parent.height
                        text: "Undo"
                        enabled: false
                        onClicked: undoClicked()
                }

                Button {
                        id: redoButton
                        flat: true
                        font.pointSize: 18
                        width: 74
                        height: parent.height
                        text: "Redo"
                        enabled: false
                        onClicked: redoClicked()
                }
        }
}
