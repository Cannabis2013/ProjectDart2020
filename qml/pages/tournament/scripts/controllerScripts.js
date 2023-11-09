.import "tournamentPageScripts.js" as Scripts
.import "tournamentModals.js" as Modals

function init() {
        const scores = JSON.parse(dartsController.playerScores())
        Scripts.initPlayerScores(scores)
        updateTurnValues()
}

function restartGame() {
        dartsController.reset()
        updateTurnValues()
}

function undo() {
        const response = dartsController.undoTurn()
        updateTurnValues()
}

function redo() {
        const response = dartsController.redoTurn()
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
        const turnInfo = JSON.parse(dartsController.turnInfo())
        if (turnInfo.winnerFound) {
                Scripts.winnerFound(turnInfo)
                Modals.openWinnerModal(turnInfo.winnerName, restartGame, undo)
        } else
                Scripts.winnerNotFound(turnInfo)
}
