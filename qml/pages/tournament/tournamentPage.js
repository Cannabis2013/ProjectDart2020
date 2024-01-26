.import "winnerModal/modalWinner.js" as WinnerModal
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

function initializeUI() {
        init()
        updateTurnValues()
}

function init() {
        const players = JSON.parse(dartsController.allPlayers())
        const scores = JSON.parse(dartsController.playerScores())
        playersSection.setPlayers(players)
        scoresSection.initializeScores(scores)
}

function restartGame() {
        dartsController.reset()
        init()
        updateTurnValues()
        tournamentPage.forceActiveFocus()
}

function undo() {
        dartsController.undoTurn()
        updateTurnValues()
        tournamentPage.forceActiveFocus()
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
        const statistics = JSON.parse(dartsController.statisticReport())
        if (turnValues.winnerFound)
                WinnerModal.openWinnerModal(turnValues, statistics, restartGame, undo)
        else
                updateSections(turnValues, statistics)
}

function updateSections(turnValues, statistics) {
        updateTurnControlsSection(turnValues)
        updatePlayerSection(turnValues)
        scoresSection.updateScores(turnValues.playerScores)
        playerStatistics.setStatistics(statistics)
        inputSection.enabled = true
}

function updatePlayerSection(turnValues) {
        const name = turnValues.currentPlayerName
        const turnIndex = turnValues.turnIndexes.turnIndex
        playersSection.highlightPlayer(name, turnIndex)
}

function updateTurnControlsSection(turnValues) {
        const indexes = turnValues.turnIndexes
        const suggestions = turnValues.suggestions
        turnControls.updateValues(indexes.canUndo, indexes.canRedo)
        messageSection.targetRow = suggestions.targetRow
}
