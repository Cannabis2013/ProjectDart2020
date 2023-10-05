function updateInitialValues() {
        const initJson = JSON.parse(dartsController.initialValues())
        const names = initJson["playerNames"]
        const scores = initJson["playerScores"]
        playerIcons.setIconLabels(names)
        scoresView.initialize(names, scores)
}

function updateTurnInfo() {
        const turnInfo = dartsController.turnInfo()
        const json = JSON.parse(turnInfo)
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
        const playerName = json["playerName"]
        const playerScore = json["playerScore"]
        scoresView.updateScore(playerScore, playerName)
}
