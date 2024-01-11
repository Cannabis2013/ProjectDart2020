import QtQuick 2.15
import QtQuick.Layouts 1.3
import "scoresSection.js" as Scripts

Item {
        id: scoresFlickable
        clip: true

        function highlightScoreRect(json) {
                Scripts.updatePlayerRect(json)
        }

        QtObject {
                id: scoreRects
                property var objects: []
        }

        property int playersCount: 0

        function initialize(players) {
                Scripts.clearNames()
                playersCount = players.length
                for (var i = 0; i < players.length; i++) {
                        const player = players[i]
                        Scripts.appendName(player.playerName, player.playerScore)
                }
        }

        function updateScores(scores) {
                for (var i = 0; i < scores.length; i++) {
                        const score = scores[i]
                        Scripts.updateScore(score.playerName, score.playerScore)
                }
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
