function initializeScores(scores) {
        for (var i = 0; i < scores.length; i++) {
                const score = scores[i]
                const scoreObj = i == 0 ? playerOneScore : playerTwoScore
                initializeScoreObject(scoreObj, score)
        }
}

function initializeScoreObject(scoreObj, score) {
        scoreObj.text = score.value
        scoreObj.name = score.name
}

function updateScore(scores) {
        for (var i = 0; i < scores.length; i++) {
                const score = scores[i]
                const scoreObj = getScoreObject(score.name)
                scoreObj.text = score.value
        }
}
function getScoreObject(name) {
        if (playerOneScore.name === name)
                return playerOneScore
        else if (playerTwoScore.name === name)
                return playerTwoScore
        else
                throw "Critical error. ScoreRect with provided name not available!"
}
