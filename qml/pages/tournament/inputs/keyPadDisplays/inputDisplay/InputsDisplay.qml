import QtQuick 6.0
import "inputsDisplay.js" as Scripts

Item {
    function inputs() {
        return Scripts.readInputs()
    }

    function hasInputs() {
        return Scripts.hasInputs()
    }

    function addInput(modId, point) {
        return Scripts.addInput(modId, point)
    }

    function popInput() {
        return Scripts.popInput()
    }

    function clear() {
        Scripts.clear()
    }

    Rectangle {
        color: "#4f4f4f"
        radius: 6
        anchors.fill: parent

        Text {
            id: textLabel
            anchors.left: parent.left
            anchors.leftMargin: 6
            anchors.top: parent.top
            anchors.topMargin: 3
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 3
            width: 36
            text: "INPUTS"
            font.pixelSize: 12
            color: "lightgray"
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: textInputs
            anchors.left: textLabel.right
            anchors.leftMargin: 12
            anchors.right: parent.right
            height: parent.height
            font.pixelSize: 18
            font.weight: Font.Bold
            color: "white"
            verticalAlignment: Text.AlignVCenter
        }
    }
}
