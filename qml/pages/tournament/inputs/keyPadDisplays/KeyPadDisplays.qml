import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "controls"
import "scorePreview"
import "scoreDisplay"
import "inputDisplay"
import "keyPadDisplays.js" as Scripts

Item {
        function hasInputs() {
                return inputsDisplay.hasInputs()
        }

        function readInputs() {
                return inputsDisplay.inputs()
        }

        function addInput(modId, point) {
                Scripts.add(modId, point)
        }

        function flushInputs() {
                Scripts.clearInputs()
        }

        ScoreDisplay {
                id: scoreDisplay
                anchors.top: parent.top
                anchors.left: scorePreview.right
                anchors.leftMargin: 6
                width: 80
                anchors.bottom: parent.verticalCenter
                anchors.bottomMargin: 6
        }

        PreviewDisplay {
                id: scorePreview
                anchors.left: parent.left
                width: 110
                anchors.top: parent.top
                anchors.bottom: parent.verticalCenter
                anchors.bottomMargin: 6
        }

        InputsDisplay {
                id: inputsDisplay
                anchors.left: parent.left
                width: 170
                anchors.top: parent.verticalCenter
                anchors.bottom: parent.bottom
                anchors.topMargin: 6
        }

        DisplayControls {
                id: displayControls
                anchors.left: inputsDisplay.right
                anchors.right: parent.right
                anchors.rightMargin: 6
                anchors.top: parent.verticalCenter
                anchors.bottom: parent.bottom
        }
}
