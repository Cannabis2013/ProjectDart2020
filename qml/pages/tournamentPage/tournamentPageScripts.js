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
        if (json["status"] === "running")
                winnerNotFound(json)
        else
                winnerFound(json)
}

function winnerNotFound(jsonObj) {
        updateTurnComp(jsonObj)
        updateScoresView(jsonObj)
        updateStatistics(jsonObj)
        updatefinish(jsonObj)
        keyPad.enabled = true
}

function winnerFound(jsonObj) {
        const playerName = jsonObj["currentPlayerName"]
        updateTurnComp(jsonObj)
        keyPad.enabled = false
        targetRow.text = `WINNER: ${playerName}`
}

function updateTurnComp(json) {
        turnInfoComp.canUndo = json["canUndo"]
        turnInfoComp.canRedo = json["canRedo"]
        turnInfoComp.turnIndex = json["turnIndex"]
}

function updateScoresView(json) {
        const player = json["currentPlayerName"]
        scoresView.highligtScore(player)
}

function sendScore(modId, point) {
        const score = {
                "mod": modId,
                "point": point
        }
        const response = dartsController.addInput(JSON.stringify(score))
        return response
}

function updatePlayerScore(response) {
        const json = JSON.parse(response)
        updateScoreView(json)
}

function updatePlayerScores(response) {
        const json = JSON.parse(response)
        for (var i = 0; i < json.length; i++)
                updateScoreView(json[i])
}

function updateScoreView(jsonObj) {
        const playerName = jsonObj["playerName"]
        const playerScore = jsonObj["playerScore"]
        scoresView.updateScore(playerScore, playerName)
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