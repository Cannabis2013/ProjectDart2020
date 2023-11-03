function appendName(name, score) {
        const objectWidth = scoresView.width / playersCount
        const component = Qt.createComponent("ScoreRect.qml")
        const object = component.createObject(scoresGrid, {})
        object.id = name
        object.setName(shortenName(name))
        object.updateScore(score)
        object.width = objectWidth
        object.Layout.fillHeight = true
        object.Layout.alignment = Qt.AlignHCenter
        scoresFlickable.contentWidth += objectWidth
        scoresObjects.objects.push(object)
}

function shortenName(name) {
        if (name.length > 16)
                return name.substring(0, 16) + ".."
        return name
}

function updateScore(name, score) {
        const objects = scoresObjects.objects
        for (var i = 0; i < objects.length; i++) {
                const scoreObject = objects[i]
                if (scoreObject.id === name)
                        scoreObject.updateScore(score)
        }
}

function updatePlayerRect(name, turnIndex) {
        const scores = scoresObjects.objects
        for (var i = 0; i < scores.length; i++) {
                const score = scores[i]
                if (score.id === name)
                        score.highlight(turnIndex)
                else
                        score.unHighlight()
        }
}

function updateStatistics(name, average, low, high) {
        const objects = scoresObjects.objects
        for (var i = 0; i < objects.length; i++) {
                const scoreObject = objects[i]
                if (scoreObject.id === name)
                        scoreObject.updateStatistics(average, low, high)
        }
}
