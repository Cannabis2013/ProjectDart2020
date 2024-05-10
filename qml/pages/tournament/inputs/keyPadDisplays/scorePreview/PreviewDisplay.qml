import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "previewDisplay.js" as Scripts

Item {
        function updateScore(score) {
                Scripts.updateScorePreview(score)
        }

        function clear() {
                Scripts.clearPreview()
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
                        height: parent.height
                        width: 44
                        text: "PREVIEW"
                        font.pixelSize: 12
                        color: "lightgray"
                        verticalAlignment: Text.AlignVCenter
                }

                Text {
                        id: textPreview
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
