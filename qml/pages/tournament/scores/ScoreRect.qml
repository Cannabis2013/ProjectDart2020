import QtQuick 2.15
import QtQuick.Layouts 1.3

Rectangle {
        id: playersScoreRect

        color: "green"

        function highlight(count) {
                playerInfo.showCounter(true)
                playerInfo.updateCounter(count)
                highlightRect.visible = true
        }

        function unHighlight() {
                playerInfo.showCounter(false)
                highlightRect.visible = false
        }

        property string id: ""

        function setName(name) {
                playerInfo.setName(name)
        }

        function updateScore(score) {
                playerScore.text = score.toString()
        }

        function updateStatistics(average, low, high) {
                statistics.updateValues(average, low, high)
        }

        property double average: 0.0

        Rectangle {
                id: highlightRect
                color: "blue"
                anchors.fill: parent
                visible: false
        }

        GridLayout {
                anchors.fill: parent
                rowSpacing: 0
                flow: GridLayout.TopToBottom

                ScoreUpperRect {
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

                StatisticsView {
                        id: statistics
                        Layout.minimumHeight: 64
                        Layout.maximumHeight: 64
                        Layout.fillWidth: true
                }
        }
}
