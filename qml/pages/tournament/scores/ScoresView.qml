import QtQuick 2.15
import QtQuick.Layouts 1.3

import "scoresScripts.js" as ScoresScripts

Flickable {
        id: scoresFlickable
        clip: true
        contentWidth: 0
        contentHeight: scoresFlickable.height

        function updateHighlightValues(json) {
                const name = json.currentPlayerName
                const turnIndex = json.turnIndexes.turnIndex
                ScoresScripts.updatePlayerRect(name, turnIndex)
        }

        QtObject {
                id: scoresObjects
                property var objects: []
        }

        property int playersCount: 0

        function appendName(json) {
                const name = json.playerName
                const score = json.playerScore
                ScoresScripts.appendName(name, score)
        }

        function updateScore(json) {
                ScoresScripts.updateScore(json.playerName, json.playerScore)
        }

        function updateStatistics(json) {
                const name = json.playerName
                const average = json.average
                const low = json.low
                const high = json.high
                ScoresScripts.updateStatistics(name, average, low, high)
        }

        GridLayout {
                id: scoresGrid
                anchors.fill: parent
                columnSpacing: 0
        }
}
