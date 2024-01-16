.import "winnerModal/winnerModal.js" as WinnerModal
.import "textModal/textModal.js" as TextModal

function handleCloseEvent(event) {
        if (event.key === Qt.Key_Back) {
                event.accepted = true
                TextModal.openBackModal(menuRequest)
        }
}

function isPortrait() {
        return tournamentPage.height > tournamentPage.width
}

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
                WinnerModal.openWinnerModal(turnValues, statisticValues, restartGame, undo)
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
        messageSection.targetRow = jsonObj.suggestions.finish
}

function updateScoresSection(scoresValues, statisticValues) {
        scoresSection.highlightScoreRect(scoresValues)
        scoresSection.updateScores(scoresValues.playerScores)
        scoresSection.updateStatistics(statisticValues)
}
