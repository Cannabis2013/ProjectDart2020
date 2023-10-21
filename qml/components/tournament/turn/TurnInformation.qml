import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls

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
                Button {
                        id: undoButton
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: "Undo"
                        enabled: false
                        onClicked: undoClicked()
                }

                Text {
                        clip: true
                        id: indexRect
                        Layout.minimumWidth: 48
                        Layout.fillHeight: true
                        text: turnRect.turnIndex
                        font.pointSize: 20
                        font.weight: Font.Bold
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                }

                Button {
                        id: redoButton
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: "Redo"
                        enabled: false
                        onClicked: redoClicked()
                }
        }
}
