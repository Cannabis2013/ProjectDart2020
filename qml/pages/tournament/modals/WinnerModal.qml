import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../turn"
import "../keyPad"

Rectangle {
        id: winnerModal
        anchors.fill: parent
        color: "black"

        signal restartClicked
        signal undoClicked

        function setPlayerDetails(name, url) {
                winnerSection.setWinnerUrl(url)
                winnerSection.setWinnerName(name)
        }

        function setStatisticsDetails(arr) {
                for (var index = 0; index < arr.length; index++) {
                        const stats = arr[index]
                        statisticsSection.setPlayerName(index, stats.name)
                        statisticsSection.setPlayerStatistic(index, stats.average, stats.low, stats.high)
                }
        }

        MouseArea {
                anchors.fill: parent
        }

        MouseArea {
                anchors.fill: parent
        }

        GridLayout {
                flow: GridLayout.TopToBottom
                anchors.centerIn: parent
                width: parent.width - 12
                height: parent.height

                SwipeView {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        WinnerSection {
                                id: winnerSection
                        }

                        StatisticsSection {
                                id: statisticsSection
                        }
                }

                WinnerControlSection {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 48
                }
        }
}
