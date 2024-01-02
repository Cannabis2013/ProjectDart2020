import QtQuick 2.15
import QtQuick.Layouts 1.3
import "scoresView.js" as Scripts

Item {
        id: scoresFlickable
        clip: true

        function updateHighlightValues(json) {
                Scripts.updatePlayerRect(json)
        }

        QtObject {
                id: scoresObjects
                property var objects: []
        }

        property int playersCount: 0

        function appendName(json) {
                Scripts.appendName(json.playerName, json.playerScore)
        }

        function updateScore(json) {
                Scripts.updateScore(json.playerName, json.playerScore)
        }

        function updateStatistics(json) {
                Scripts.updateStatistics(json)
        }

        GridLayout {
                id: scoresGrid
                anchors.fill: parent
                columnSpacing: 0
        }
}
