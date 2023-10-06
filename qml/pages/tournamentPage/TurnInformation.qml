import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15

import "../../components/playerIcons"
import "../../components/playerScores"
import "../../components/pages"
import "../../components/buttons"

import "tournamentPageScripts.js" as PageScripts

Rectangle {
        clip: true
        color: "transparent"

        signal undoClicked
        signal redoClicked

        property bool canUndo: undoButton.enabled
        onCanUndoChanged: undoButton.enabled = canUndo

        property bool canRedo: redoButton.enabled
        onCanRedoChanged: redoButton.enabled = canRedo

        GridLayout {
                anchors.fill: parent

                Rectangle {
                        Layout.fillWidth: true
                }

                NewPushButton {
                        id: undoButton
                        Layout.alignment: Qt.AlignLeft
                        width: 48
                        Layout.fillHeight: true
                        text: "Undo"
                        backgroundColor: "grey"
                        radius: 6
                        enabled: false
                        onClicked: undoClicked()
                }

                NewPushButton {
                        id: redoButton
                        Layout.alignment: Qt.AlignLeft
                        width: 48
                        Layout.fillHeight: true
                        text: "Redo"
                        backgroundColor: "grey"
                        radius: 6
                        enabled: false
                        onClicked: redoClicked()
                }

                Rectangle {
                        Layout.fillWidth: true
                }
        }
}
