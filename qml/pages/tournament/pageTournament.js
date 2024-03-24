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
        dartsInitializer.reset()
        initializeUI()
        tournamentPage.forceActiveFocus()
}

function undo() {
        dartsTurns.undo()
        updateTurnValues()
        tournamentPage.forceActiveFocus()
}

function redo() {
        dartsTurns.redo()
        updateTurnValues()
}

function addScore(scores) {
        const json = JSON.stringify(scores)
        dartsInputs.add(json)
        updateTurnValues()
}

function bustScore() {
        dartsTurns.skip()
        updateTurnValues()
}

function updateTurnValues() {
        if (dartsPlayers.isWinnerFound())
                Dialogs.openWinnerDialog(restartGame, undo)
        else
                updateSections()
}

function updateSections() {
        playerInfos.update()
        turnControls.update()
        messageSection.update()
}
