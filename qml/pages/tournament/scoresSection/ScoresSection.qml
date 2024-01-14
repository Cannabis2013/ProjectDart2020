import QtQuick 2.15
import QtQuick.Layouts 1.3
import "scoresSection.js" as Scripts

Item {
        QtObject {
                id: scoreRects
                property var objects: []
        }

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
        }
}
