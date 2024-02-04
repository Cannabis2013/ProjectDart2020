.import "dialogs/dialogs.js" as Dialogs

function handleCloseEvent(event) {
        if (event.key === Qt.Key_Back) {
                event.accepted = true
                Dialogs.openQuitDialog(menuRequest)
        }
}

function isPortrait() {
        return tournamentPage.height > tournamentPage.width
}

function initializeUI() {
        playerInfos.initialize()
        updateTurnValues()
}

function restartGame() {
        dartsController.reset()
        initializeUI()
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
        const jsonReport = JSON.parse(dartsController.turnReport())
        const turnInfo = jsonReport.turnInfo
        if (turnInfo.winnerFound)
                Dialogs.openWinnerDialog(jsonReport, restartGame, undo)
        else
                updateSections(jsonReport)
}

function updateSections(jsonReport) {
        playerInfos.setValues(jsonReport)
        turnControls.updateValues(jsonReport)
        messageSection.targetRow = jsonReport.suggestions.targetRow
}
