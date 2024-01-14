function initialize(players) {
        clearNames()
        setPlayers(players)
}

function setPlayers(players) {
        playersCount = players.length
        for (var i = 0; i < players.length; i++) {
                const player = players[i]
                appendName(player.playerName, player.playerScore)
        }
}

function clearNames() {
        scoresGrid.children = []
        scoreRects.objects = []
}

function appendName(name, score) {
        const objectWidth = scoresSection.width / playersCount
        const component = Qt.createComponent("ScoreRect.qml")
        const object = component.createObject(scoresGrid, {})
        object.id = name
        object.setName(shortenName(name))
        object.updateScore(score)
        object.Layout.fillWidth = true
        object.Layout.fillHeight = true
        object.Layout.alignment = Qt.AlignHCenter
        scoreRects.objects.push(object)
}

function shortenName(name) {
        if (name.length > 16)
                return name.substring(0, 16) + ".."
        return name
}

function updateScore(scores) {
        for (var i = 0; i < scores.length; i++) {
                const score = scores[i]
                const scoreRect = getScoreRect(score.playerName)
                scoreRect.updateScore(score.playerScore)
        }
}

function highlightScoreRect(name, turnIndex) {
        const scores = scoreRects.objects
        for (var i = 0; i < scoreRects.objects.length; i++) {
                const score = scores[i]
                if (score.id === name)
                        score.highlight(turnIndex)
                else
                        score.unHighlight()
        }
}

function updateStatistics(statisticValues) {
        for (var i = 0; i < statisticValues.length; i++) {
                const statisticValue = statisticValues[i]
                const scoreRect = getScoreRect(statisticValue.name)
                scoreRect.updateStatistics(statisticValue)
        }
}

function getScoreRect(name) {
        const objects = scoreRects.objects
        for (var i = 0; i < objects.length; i++) {
                const scoreObject = objects[i]
                if (scoreObject.id === name)
                        return scoreObject
        }
        return null
}
