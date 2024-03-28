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

        ScoreDisplay {
                id: textDisplay
                anchors.left: parent.left
                anchors.leftMargin: 12
                anchors.right: clearButton.left
                anchors.rightMargin: 12
                height: parent.height
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
