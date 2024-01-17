import QtQuick 2.15
import QtQuick.Layouts 1.3
import "scoreRect.js" as Scripts

Rectangle {
        id: playersScoreRect

        color: "green"

        function highlight(count) {
                Scripts.highlight(true, count)
        }

        function unHighlight() {
                Scripts.highlight(false, 0)
        }

        readonly property string name: playerInfo.name

        function setName(name) {
                playerInfo.name = name
        }

        function updateScore(score) {
                playerScore.text = score.toString()
        }

        function updateStatistics(statisticValues) {
                Scripts.updateStatistics(statisticValues)
        }

        GridLayout {
                anchors.centerIn: parent
                width: parent.width - 12
                height: parent.height
                rowSpacing: 0
                flow: GridLayout.TopToBottom

                PlayerInfo {
                        id: playerInfo
                        Layout.fillWidth: true
                        Layout.preferredHeight: 52
                }

                Text {
                        id: playerScore
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        font.pointSize: 100
                        font.weight: Font.Bold
                        color: "white"
                        verticalAlignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                }

                PlayerStatistics {
                        id: playerStatistics
                        Layout.preferredHeight: 48
                        Layout.fillWidth: true
                }
        }
}
