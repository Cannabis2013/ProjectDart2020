import QtQuick 2.15
import QtQuick.Layouts 1.3

import "./scoresScripts.js" as ScoresScripts

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

        signal appendName(string name, int score)
        onAppendName: (name, score) => ScoresScripts.appendName(name, score)

        signal highligtScore(string name)
        onHighligtScore: name => ScoresScripts.highlightScore(name)

        signal updateScore(string name, int score)
        onUpdateScore: (name, score) => ScoresScripts.updateScore(name, score)

        signal updateStatistics(string name, double average, int low, int high)
        onUpdateStatistics: (name, average, low, high) => ScoresScripts.updateStatistics(name, average, low, high)

        GridLayout {
                id: scoresGrid
                anchors.fill: parent
                columnSpacing: 0
        }
}
