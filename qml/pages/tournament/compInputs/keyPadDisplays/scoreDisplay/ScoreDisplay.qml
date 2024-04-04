import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "scoreDisplay.js" as Scripts

Item {
        function addScore(modId, point) {
                return Scripts.add(modId, point)
        }

        function subtrackScore(modId, point) {
                return Scripts.subtract(modId, point)
        }

        function clear() {
                Scripts.clear()
        }

        Rectangle {
                id: scorePreview
                color: "#4f4f4f"
                radius: 6
                anchors.fill: parent

                Rectangle {
                        id: textLabel
                        color: "blue"
                        anchors.left: parent.left
                        anchors.leftMargin: 6
                        anchors.top: parent.top
                        anchors.topMargin: 3
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 3
                        width: 64
                        radius: 6
                        Text {
                                anchors.fill: parent
                                text: "Score"
                                font.pixelSize: 16
                                font.weight: Font.Bold
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                        }
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
