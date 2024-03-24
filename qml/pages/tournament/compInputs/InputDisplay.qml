import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "inputDisplay.js" as Scripts

Item {
        QtObject {
                id: inputMemory
                property var inputs: []
        }

        function hasInputs() {
                return inputMemory.inputs.length > 0
        }

        function readInputs() {
                return inputMemory.inputs
        }

        function addInput(modId, point) {
                Scripts.addInput(modId, point)
        }

        function flushInputs() {
                Scripts.clearInputs()
        }

        Item {
                anchors.left: parent.left
                anchors.right: clearButton.left
                height: parent.height
                Rectangle {
                        color: "#4f4f4f"
                        radius: 12
                        width: 200
                        height: 54
                        anchors.centerIn: parent
                        Text {
                                id: inputsText
                                color: "white"
                                font.pointSize: 32
                                width: 182
                                height: parent.height
                                anchors.centerIn: parent
                                verticalAlignment: Text.AlignVCenter
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
