import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls

import "scripts.js" as Scripts

Rectangle {
        id: turnRect
        color: "transparent"
        signal undoClicked
        signal redoClicked

        function updateValues(turnObj, rowObj) {
                Scripts.update(turnObj, rowObj)
        }

        GridLayout {
                anchors.fill: parent
                Button {
                        id: undoButton
                        flat: true
                        font.pointSize: 16
                        Layout.minimumWidth: 64
                        Layout.maximumWidth: 64
                        Layout.fillHeight: true
                        text: "Undo"
                        enabled: false
                        onClicked: undoClicked()
                }

                Button {
                        id: redoButton
                        flat: true
                        font.pointSize: 16
                        Layout.minimumWidth: 64
                        Layout.maximumWidth: 64
                        Layout.fillHeight: true
                        text: "Redo"
                        enabled: false
                        onClicked: redoClicked()
                }

                Text {
                        clip: true
                        id: messageRect
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        font.pointSize: 16
                        font.weight: Font.Bold
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                }
        }
}
