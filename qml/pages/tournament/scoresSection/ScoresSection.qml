import QtQuick 2.15
import QtQuick.Layouts 1.3
import "scoresSection.js" as Scripts

Item {
        function highlightScoreRect(json) {
                Scripts.highlightScoreRect(json.currentPlayerName, json.turnIndexes.turnIndex)
        }

        property int playersCount: 0

        function initialize(players) {
                Scripts.initialize(players)
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

                ScoreRect {
                        id: scoreRectOne
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                }

                ScoreRect {
                        id: scoreRectTwo
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                }
        }
}
