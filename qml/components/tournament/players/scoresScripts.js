function appendName(name, score) {
        const objectWidth = scoresView.width / playersCount
        const component = Qt.createComponent("PlayerScore.qml")
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
        if (name.length > 8)
                return name.substring(0, 8) + ".."
        return name
}

function highlightScore(name) {
        const scores = scoresObjects.objects
        for (var i = 0; i < scores.length; i++) {
                const score = scores[i]
                if (score.id === name)
                        score.highlighted = true
                else
                        score.highlighted = false
        }
}

function updateScore(name, score) {
        const objects = scoresObjects.objects
        for (var i = 0; i < objects.length; i++) {
                const scoreObject = objects[i]
                if (scoreObject.id === name)
                        scoreObject.updateScore(score)
        }
}

function updateStatistics(name, average, low, high) {
        const objects = scoresObjects.objects
        for (var i = 0; i < objects.length; i++) {
                const scoreObject = objects[i]
                if (scoreObject.id === name)
                        scoreObject.updateStatistic(average, low, high)
        }
}
