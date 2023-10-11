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
        updateScoresView(jsonObj)
        updatePlayerScores(jsonObj["playerScores"])
        updateStatistics(jsonObj["statistics"])
        updatefinish(jsonObj["suggestions"])
        keyPad.enabled = true
}

function winnerFound(jsonObj) {
        const playerName = jsonObj["currentPlayerName"]
        updateTurnComp(jsonObj["turnIndexes"])
        updatePlayerScores(jsonObj["playerScores"])
        keyPad.enabled = false
        targetRow.text = `WINNER: ${playerName}`
}

function updateTurnComp(json) {
        turnInfoComp.canUndo = json["canUndo"]
        turnInfoComp.canRedo = json["canRedo"]
        turnInfoComp.turnIndex = json["throwIndex"]
}

function updateScoresView(jsonObj) {
        const player = jsonObj["currentPlayerName"]
        scoresView.highligtScore(player)
}

function updatePlayerScores(jsonArr) {
        for (var i = 0; i < jsonArr.length; i++) {
                const jsonObj = jsonArr[i]
                const playerName = jsonObj["playerName"]
                const playerScore = jsonObj["playerScore"]
                print(playerName)
                scoresView.updateScore(playerScore, playerName)
        }
}

function updateStatistics(jsonObj) {
        const average = jsonObj["average"]
        const low = jsonObj["low"]
        const high = jsonObj["high"]
        const text = `Average: ${average} - Low: ${low} - High: ${high}`
        statistics.text = text
}

function updatefinish(jsonObj) {
        targetRow.text = jsonObj["finish"]
}
