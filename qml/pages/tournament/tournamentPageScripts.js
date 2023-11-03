function init() {
        initPlayerScores()
        updateTurnInfo()
}

function initPlayerScores() {
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

function winnerNotFound(json) {
        updateTurnComponents(json)
        highlightScoreBox(json)
        updateScoreBoxes(json["playerScores"], json["statistics"])
        keyPad.enabled = true
}

function winnerFound(jsonObj) {
        const playerName = jsonObj["winnerName"]
        updateTurnComponents(jsonObj)
        updateScoreBoxes(jsonObj["playerScores"], jsonObj["statistics"])
        keyPad.enabled = false
        winnerModal.show(jsonObj["winnerName"])
}

function updateTurnComponents(jsonObj) {
        const indexes = jsonObj.turnIndexes
        turnControls.updateValues(indexes.canUndo, indexes.canRedo)
        targetRow.text = jsonObj.suggestions.finish
}

function highlightScoreBox(json) {
        const name = json.currentPlayerName
        const turnIndex = json.turnIndexes.turnIndex
        scoresView.updatePlayerValues(name, turnIndex)
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

function restartGame() {
        dartsController.reset()
        updateTurnInfo()
}

function undo() {
        const response = dartsController.undoTurn()
        updateTurnInfo()
}

function redo() {
        const response = dartsController.redoTurn()
        updateTurnInfo()
}

function addScore(modId, point) {
        dartsController.addInput(modId, point)
        updateTurnInfo()
}

function bustScore() {
        dartsController.skipTurn()
        updateTurnInfo()
}
