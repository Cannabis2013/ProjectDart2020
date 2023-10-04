import QtQuick 2.15
import QtQuick.Layouts 1.3

Flickable {
        id: scoresFlickable
        clip: true
        contentWidth: 384
        contentHeight: 80

        QtObject {
                id: scoresObjects
                property var objects: []
        }

        signal setNames(var names)
        onSetNames: {
                for (var i = 0; i < names.length; i++) {
                        const component = Qt.createComponent("PlayerScore.qml")
                        const object = component.createObject(scoresGrid, {})
                        object.setName(names[i])
                        scoresGrid.width += 128
                        scoresFlickable.contentWidth += 128
                        scoresObjects.objects.push(object)
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
                width: 0
        }
}
