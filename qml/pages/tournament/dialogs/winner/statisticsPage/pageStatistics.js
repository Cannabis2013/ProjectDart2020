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
        let rounds = finishedRounds()
        roundsText.text = `Rounds: ${rounds}`
}

function finishedRounds() {
        const report = JSON.parse(dartsTurns.report())
        let round = report.roundIndex
        const turnId = report.turnId
        if (round > 1 && turnId % 2 == 0)
                round--
        return round
}
