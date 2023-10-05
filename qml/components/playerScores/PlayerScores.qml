import QtQuick 2.15
import QtQuick.Layouts 1.3

Flickable {
        id: scoresFlickable
        clip: true
        contentWidth: 0
        contentHeight: 80

        QtObject {
                id: scoresObjects
                property var objects: []
        }

        signal initialize(var names, var scores)
        onInitialize: {
                for (var i = 0; i < names.length; i++) {
                        const component = Qt.createComponent("PlayerScore.qml")
                        const object = component.createObject(scoresGrid, {})
                        object.setName(names[i])
                        object.setScore(scores[i])
                        const objectWidth = i < names.length - 1 ? 134 : 128
                        scoresGrid.width += objectWidth
                        scoresFlickable.contentWidth += objectWidth
                        scoresObjects.objects.push(object)
                }
        }

        signal highligtScore(string name)
        onHighligtScore: {
                const scores = scoresObjects.objects
                for (var i = 0; i < scores.length; i++) {
                        const score = scores[i]
                        const scoreName = score.name
                        if (scoreName === name)
                                score.highlighted = true
                        else
                                score.highlighted = false
                }
        }

        signal updateScore(int score, string name)
        onUpdateScore: {
                const objects = scoresObjects.objects
                for (var i = 0; i < objects.length; i++) {
                        const scoreObject = objects[i]
                        if (scoreObject.name === name)
                                scoreObject.setScore(score)
                }
        }

        GridLayout {
                id: scoresGrid
                columnSpacing: 6
                width: 0
        }
}
