import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls

import "../../../sharedComponents/geometry"
import "../../../sharedComponents/buttons"
import "scripts.js" as Scripts

TransparentRect {
        id: turnRect

        signal undoClicked
        signal redoClicked

        function updateValues(turnObj, rowObj) {
                Scripts.update(turnObj, rowObj)
        }

        GridLayout {
                anchors.fill: parent
                PushButton {
                        id: undoButton
                        Layout.minimumWidth: 64
                        Layout.maximumWidth: 64
                        fontSize: 20
                        Layout.fillHeight: true
                        buttonText: "Undo"
                        enabled: false
                        onClicked: undoClicked()
                }

                PushButton {
                        id: redoButton
                        Layout.minimumWidth: 64
                        Layout.maximumWidth: 64
                        Layout.fillHeight: true
                        fontSize: 20
                        buttonText: "Redo"
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
