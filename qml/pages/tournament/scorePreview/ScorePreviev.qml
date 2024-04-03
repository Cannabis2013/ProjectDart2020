import QtQuick 2.15
import "scorePreview.js" as Scripts

Rectangle {
        function updateScore(score) {
                Scripts.show(score)
        }

        color: "black"
        radius: 6
        opacity: 0

        Behavior on opacity {
                NumberAnimation {
                        duration: 250
                }
        }

        Text {
                id: textPreview
                anchors.fill: parent
                font.pixelSize: 40
                font.weight: Font.Bold
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
        }
}
