import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "dialogWinner.js" as Scripts
import "winnerPage"
import "statisticsPage"

Rectangle {
        id: winnerModal
        anchors.fill: parent
        color: "black"

        signal restartClicked
        signal undoClicked

        function setPlayerDetails(playerDetails) {
                pageWinner.setPlayerDetails(playerDetails)
        }

        function setStatisticsDetails(statistics) {
                pageStatistics.setPlayerStatistics(statistics)
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
                        PageWinner {
                                id: pageWinner
                        }

                        PageStatistics {
                                id: pageStatistics
                        }
                }

                DialogButtons {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 48
                }
        }
}
