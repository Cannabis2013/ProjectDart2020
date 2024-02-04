import QtQuick 2.15
import QtQuick.Layouts 1.3
import "compScoreDisplay.js" as Scripts

Item {
        id: scoreDisplay

        height: 116

        function initScore(score) {
                Scripts.initScoreDisplay(score)
        }

        function updateScore(score) {
                Scripts.updateScoreDisplay(score)
        }

        Text {
                id: scoreDisplayText
                anchors.fill: parent
                font.pointSize: 100
                font.weight: Font.Bold
                color: "white"
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignHCenter
        }
}
