function initialize(players) {
        setPlayers(players)
}

function setPlayers(players) {
        playersCount = players.length
        for (var i = 0; i < players.length; i++) {
                const player = players[i]
                const scoreRect = i == 0 ? scoreRectOne : scoreRectTwo
                initializeScoreRect(scoreRect, player.playerName, player.playerScore)
        }
}

function initializeScoreRect(scoreRect, name, score) {
        scoreRect.setName(shortenName(name))
        scoreRect.updateScore(score)
        scoreRect.Layout.fillWidth = true
        scoreRect.Layout.fillHeight = true
        scoreRect.Layout.alignment = Qt.AlignHCenter
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
        if (scoreRectOne.name === name) {
                scoreRectOne.highlight(turnIndex)
                scoreRectTwo.unHighlight()
        } else if (scoreRectTwo.name === name) {
                scoreRectTwo.highlight(turnIndex)
                scoreRectOne.unHighlight()
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
        if (scoreRectOne.name === name)
                return scoreRectOne
        else if (scoreRectTwo.name === name)
                return scoreRectTwo
        else
                throw "Critical error. ScoreRect with provided name not available!"
}
