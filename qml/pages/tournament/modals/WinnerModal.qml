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

        function setStatisticsDetails(arr) {}

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
                height: parent.height - 12

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
