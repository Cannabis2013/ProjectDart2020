import QtQuick 2.15
import QtQuick.Layouts 1.3

Item {
        function initScore(score) {
                scoreDisplayText.text = score
        }

        function updateScore(score) {
                scoreDisplayText.text = score
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
