function initPlayerScores(scores) {
        scoresView.playersCount = scores.length
        for (var i = 0; i < scores.length; i++)
                scoresView.appendName(scores[i])
}

function winnerNotFound(json) {
        updateTurnComponents(json)
        scoresView.updateHighlightValues(json)
        updateScoreBoxes(json["playerScores"], json["statistics"])
        keyPad.enabled = true
}

function winnerFound(json) {
        updateTurnComponents(json)
        updateScoreBoxes(json.playerScores, json.statistics)
        keyPad.enabled = false
}

function updateTurnComponents(jsonObj) {
        const indexes = jsonObj.turnIndexes
        turnControls.updateValues(indexes.canUndo, indexes.canRedo)
        targetRow.text = jsonObj.suggestions.finish
}

function updateScoreBoxes(scores, statistics) {
        for (var i = 0; i < scores.length; i++) {
                scoresView.updateScore(scores[i])
                scoresView.updateStatistics(statistics[i])
        }
}
