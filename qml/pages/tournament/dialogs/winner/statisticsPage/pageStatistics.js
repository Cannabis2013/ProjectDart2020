function init() {
        updateScores()
        updateStatistics()
        updateTurnInfo()
}

function updateScores() {
        const playerOneScore = dartsScores.playerOne()
        const playerTwoScore = dartsScores.playerTwo()
        playerOneItem.setScore(playerOneScore)
        playerTwoItem.setScore(playerTwoScore)
}

function updateStatistics() {
        const playerOneReport = JSON.parse(dartsStats.playerOne())
        const playerTwoReport = JSON.parse(dartsStats.playerTwo())
        playerOneItem.setStatistics(playerOneReport)
        playerTwoItem.setStatistics(playerTwoReport)
}

function updateTurnInfo() {
        const report = JSON.parse(dartsTurns.report())
        const round = report.roundIndex + 1
        const text = `Rounds: ${round}`
        roundsText.text = text
}
