import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "inputDisplay.js" as Scripts

Item {
        function hasInputs() {
                return Scripts.hasInputs()
        }

        function readInputs() {
                return Scripts.readInputs()
        }

        function addInput(modId, point) {
                Scripts.addInput(modId, point)
        }

        function flushInputs() {
                Scripts.clearInputs()
        }

        Item {
                anchors.left: parent.left
                anchors.leftMargin: 12
                anchors.right: clearButton.left
                anchors.rightMargin: 12
                height: parent.height
                Rectangle {
                        clip: true
                        color: "#4f4f4f"
                        radius: 12
                        width: parent.width
                        height: 32
                        anchors.centerIn: parent
                        Text {
                                id: inputsText
                                color: "white"
                                font.pixelSize: 24
                                font.weight: Font.Bold
                                width: 182
                                height: parent.height
                                anchors.left: parent.left
                                anchors.leftMargin: 12
                                verticalAlignment: Text.AlignVCenter
                        }

                        Rectangle {
                                color: "white"
                                width: 1
                                height: parent.height
                                anchors.right: scoreText.left
                        }

                        Text {
                                id: scoreText
                                anchors.right: parent.right
                                anchors.rightMargin: 12
                                width: 48
                                height: parent.height
                                font.pixelSize: 24
                                color: "white"
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignRight
                        }
                }
        }

        Button {
                id: clearButton
                text: "Clear"
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                width: 100
                anchors.right: parent.right
                anchors.rightMargin: 12
                padding: 0
                onClicked: Scripts.clearInputs()
        }
}
