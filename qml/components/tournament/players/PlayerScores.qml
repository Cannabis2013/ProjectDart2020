import QtQuick 2.15
import QtQuick.Layouts 1.3

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

        signal appendName(var name, var score)
        onAppendName: {
                const objectWidth = scoresView.width / playersCount
                const component = Qt.createComponent("PlayerScore.qml")
                const object = component.createObject(scoresGrid, {})
                object.id = name
                object.setName(shortenName(name))
                object.setScore(score)
                object.width = objectWidth
                object.Layout.fillHeight = true
                object.Layout.alignment = Qt.AlignHCenter
                scoresFlickable.contentWidth += objectWidth
                scoresObjects.objects.push(object)
        }

        function shortenName(name) {
                if (name.length > 8)
                        return name.substring(0, 8) + ".."
                return name
        }

        signal highligtScore(string name)
        onHighligtScore: {
                const scores = scoresObjects.objects
                for (var i = 0; i < scores.length; i++) {
                        const score = scores[i]
                        if (score.id === name)
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
                        if (scoreObject.id === name)
                                scoreObject.setScore(score)
                }
        }

        GridLayout {
                id: scoresGrid
                anchors.fill: parent
                columnSpacing: 0
        }
}
