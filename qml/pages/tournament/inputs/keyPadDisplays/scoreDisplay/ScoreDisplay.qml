import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "scoreDisplay.js" as Scripts

Item {
    function addScore(score) {
        return Scripts.add(score)
    }

    function subtractScore(score) {
        return Scripts.subtract(score)
    }

    function clear() {
        textScore.text = ""
    }

    Rectangle {
        id: scorePreview
        color: "#4f4f4f"
        radius: 6
        anchors.fill: parent

        Text {
            id: textLabel
            anchors.left: parent.left
            anchors.leftMargin: 6
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: 32
            text: "SCORE"
            font.pixelSize: 12
            color: "lightgray"
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: textScore
            anchors.left: textLabel.right
            anchors.leftMargin: 6
            anchors.right: parent.right
            height: parent.height
            font.pixelSize: 18
            font.weight: Font.Bold
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
