function updateInitialValues() {
        const jsonArr = JSON.parse(dartsController.playerScores())
        for (var i = 0; i < jsonArr.length; i++) {
                const json = jsonArr[i]
                const playerName = json["playerName"]
                const playerScore = json["playerScore"]
                playerIcons.appendIconLabel(playerName)
                scoresView.appendName(playerName, playerScore)
        }
}

function updateTurnInfo() {
        const json = JSON.parse(dartsController.turnInfo())
        updateTurnComp(json)
        updateScoresView(json)
}

function updateTurnComp(json) {
        turnInfoComp.canUndo = json["canUndo"]
        turnInfoComp.canRedo = json["canRedo"]
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
