function updateInitialValues() {
        const jsonArr = JSON.parse(dartsController.playerScores())
        scoresView.playersCount = jsonArr.length
        for (var i = 0; i < jsonArr.length; i++) {
                const json = jsonArr[i]
                const playerName = json["playerName"]
                const playerScore = json["playerScore"]
                scoresView.appendName(playerName, playerScore)
        }
}

function updateTurnInfo() {
        const json = JSON.parse(dartsController.turnInfo())
        if (json["winnerFound"])
                winnerFound(json)
        else
                winnerNotFound(json)
}

function winnerNotFound(jsonObj) {
        updateTurnComp(jsonObj["turnIndexes"])
        highlightScoreBox(jsonObj)
        updateScoreBoxes(jsonObj["playerScores"], jsonObj["statistics"])
        updatefinish(jsonObj["suggestions"])
        keyPad.enabled = true
}

function winnerFound(jsonObj) {
        const playerName = jsonObj["winnerName"]
        updateTurnComp(jsonObj["turnIndexes"])
        updateScoreBoxes(jsonObj["playerScores"], jsonObj["statistics"])
        keyPad.enabled = false
        targetRow.text = `WINNER: ${playerName}`
}

function updateTurnComp(json) {
        turnInfoComp.canUndo = json["canUndo"]
        turnInfoComp.canRedo = json["canRedo"]
        turnInfoComp.turnIndex = json["turnIndex"] + 1
}

function highlightScoreBox(jsonObj) {
        const player = jsonObj["currentPlayerName"]
        scoresView.highligtScore(player)
}

function updateScoreBoxes(scoresArr, statisticsArr) {
        for (var i = 0; i < scoresArr.length; i++) {
                updateScore(scoresArr[i])
                updateStatistic(statisticsArr[i])
        }
}

function updateScore(jsonObj) {
        const playerName = jsonObj["playerName"]
        const playerScore = jsonObj["playerScore"]
        scoresView.updateScore(playerName, playerScore)
}

function updateStatistic(jsonObj) {
        const playerName = jsonObj["playerName"]
        const average = jsonObj["average"]
        const low = jsonObj["low"]
        const high = jsonObj["high"]
        scoresView.updateStatistics(playerName, average, low, high)
}

function updatefinish(jsonObj) {
        targetRow.text = jsonObj["finish"]
}
