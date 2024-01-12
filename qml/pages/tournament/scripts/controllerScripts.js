.import "tournamentModals.js" as Modals

function init() {
        const scores = JSON.parse(dartsController.playerScores())
        scoresSection.initialize(scores)
        updateTurnValues()
}

function restartGame() {
        dartsController.reset()
        init()
}

function undo() {
        dartsController.undoTurn()
        updateTurnValues()
}

function redo() {
        dartsController.redoTurn()
        updateTurnValues()
}

function addScore(modId, point) {
        dartsController.addInput(modId, point)
        updateTurnValues()
}

function bustScore() {
        dartsController.skipTurn()
        updateTurnValues()
}

function updateTurnValues() {
        const turnValues = JSON.parse(dartsController.turnReport())
        const statisticValues = JSON.parse(dartsController.statisticReport())
        if (turnValues.winnerFound) {
                Modals.openWinnerModal(turnValues, statisticValues, restartGame, undo)
        } else
                updateSections(turnValues, statisticValues)
}

function updateSections(turnValues, statisticValues) {
        updateTurnControlsSection(turnValues)
        updateScoresSection(turnValues, statisticValues)
        inputSection.enabled = true
}

function updateTurnControlsSection(jsonObj) {
        const indexes = jsonObj.turnIndexes
        turnControls.updateValues(indexes.canUndo, indexes.canRedo)
        targetRow.text = jsonObj.suggestions.finish
}

function updateScoresSection(scoresValues, statisticValues) {
        scoresSection.highlightScoreRect(scoresValues)
        scoresSection.updateScores(scoresValues.playerScores)
        scoresSection.updateStatistics(statisticValues)
}
