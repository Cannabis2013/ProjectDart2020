import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        id: playersScoreRect

        color: "green"

        function highlight(count) {
                playerInfo.showCounter(true)
                playerInfo.updateCounter(count)
                playersScoreRect.color = "blue"
        }

        function unHighlight() {
                playerInfo.showCounter(false)
                playersScoreRect.color = "green"
        }

        property string id: ""

        function setName(name) {
                playerInfo.setName(name)
        }

        function updateScore(score) {
                playerScore.text = score.toString()
        }

        function updateStatistics(average, low, high) {
                playerStatistics.updateValues(average, low, high)
        }

        GridLayout {
                anchors.fill: parent
                rowSpacing: 0
                flow: GridLayout.TopToBottom

                PlayerInfo {
                        id: playerInfo
                        Layout.fillWidth: true
                        Layout.minimumHeight: 48
                        Layout.maximumHeight: 48
                }

                Text {
                        id: playerScore
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.pointSize: 96
                        font.weight: Font.Bold
                        color: "white"
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                }

                PlayerStatistics {
                        id: playerStatistics
                        Layout.minimumHeight: 64
                        Layout.maximumHeight: 64
                        Layout.fillWidth: true
                }
        }
}
