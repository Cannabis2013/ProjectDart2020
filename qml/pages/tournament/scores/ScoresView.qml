import QtQuick 2.15
import QtQuick.Layouts 1.3

import "scoresScripts.js" as ScoresScripts

Flickable {
        id: scoresFlickable
        clip: true
        contentWidth: 0
        contentHeight: scoresFlickable.height

        QtObject {
                id: scoresObjects
                property var objects: []
        }

        property int playersCount: 0

        function appendName(name, score) {
                ScoresScripts.appendName(name, score)
        }

        function updatePlayerValues(name, turnIndex) {
                ScoresScripts.updatePlayerRect(name, turnIndex)
        }

        function updateScore(name, score) {
                ScoresScripts.updateScore(name, score)
        }

        function updateStatistics(name, average, low, high) {
                ScoresScripts.updateStatistics(name, average, low, high)
        }

        GridLayout {
                id: scoresGrid
                anchors.fill: parent
                columnSpacing: 0
        }
}
