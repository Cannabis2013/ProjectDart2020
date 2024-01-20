import QtQuick 2.15
import QtQuick.Layouts 1.3
import "scoresSection.js" as Scripts

Rectangle {
        color: "green"

        function initializeScores(scores) {
                Scripts.initializeScores(scores)
        }

        function updateScores(scores) {
                Scripts.updateScore(scores)
        }

        function updateStatistics(statisticValues) {
                Scripts.updateStatistics(statisticValues)
        }

        GridLayout {
                id: scoresGrid
                anchors.fill: parent
                columnSpacing: 0

                Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Text {
                                id: playerOneScore
                                anchors.fill: parent
                                property string name: ""
                                font.pointSize: 100
                                font.weight: Font.Bold
                                color: "white"
                                verticalAlignment: Qt.AlignVCenter
                                horizontalAlignment: Qt.AlignHCenter
                        }
                }

                Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Text {
                                id: playerTwoScore
                                anchors.fill: parent
                                property string name: ""
                                font.pointSize: 100
                                font.weight: Font.Bold
                                color: "white"
                                verticalAlignment: Qt.AlignVCenter
                                horizontalAlignment: Qt.AlignHCenter
                        }
                }
        }
}
