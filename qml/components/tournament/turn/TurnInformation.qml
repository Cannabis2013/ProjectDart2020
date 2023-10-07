import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15

import "../../../components/pages"
import "../../../components/buttons"
import "../../../components/geometry"

TransparentRect {
        id: turnRect

        signal undoClicked
        signal redoClicked

        property string turnIndex: "0"
        onTurnIndexChanged: indexRect.text = turnIndex
        property bool canUndo: undoButton.enabled
        onCanUndoChanged: undoButton.enabled = canUndo
        property bool canRedo: redoButton.enabled
        onCanRedoChanged: redoButton.enabled = canRedo

        GridLayout {
                anchors.fill: parent
                NewPushButton {
                        id: undoButton
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: "Undo"
                        backgroundColor: "grey"
                        radius: 6
                        enabled: false
                        onClicked: undoClicked()
                }

                Text {
                        clip: true
                        id: indexRect
                        Layout.minimumWidth: 48
                        Layout.fillHeight: true
                        text: turnRect.turnIndex
                        font.pointSize: 12
                        font.weight: Font.Bold
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                }

                NewPushButton {
                        id: redoButton
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: "Redo"
                        backgroundColor: "grey"
                        radius: 6
                        enabled: false
                        onClicked: redoClicked()
                }
        }
}
