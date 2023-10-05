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
        const score = json["currentPlayerScore"]
        const player = json["currentPlayerName"]
        scoresView.updateScore(score, player)
        scoresView.highligtScore(player)
}
