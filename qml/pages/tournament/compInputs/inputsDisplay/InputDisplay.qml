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
                anchors.right: removeButton.left
                anchors.rightMargin: 12
                height: parent.height
        }

        Button {
                id: removeButton
                height: 32
                width: 70
                font.pixelSize: 12
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: clearButton.left
                anchors.rightMargin: 6
                text: "Pop"
                onClicked: Scripts.removeOne()
        }

        Button {
                id: clearButton
                text: "Clear"
                height: 32
                width: 80
                font.pixelSize: 12
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 12
                onClicked: Scripts.clearInputs()
        }
}
