function init() {
        const players = JSON.parse(dartsController.allPlayers())
        const scores = JSON.parse(dartsController.playerScores())
        initPlayers(players)
        initScores(scores)
}

function initPlayers(players) {
        if (players.length !== 2)
                return
        playerOneInfo.setPlayer(players[0])
        playerTwoInfo.setPlayer(players[1])
}

function initScores(scores) {
        if (scores.length !== 2)
                return
        playerOneScore.initScore(scores[0])
        playerTwoScore.initScore(scores[1])
}

function setValues(turnReport) {
        setScores(turnReport.scoresReport.scores)
        setStatistics(turnReport.statsReport)
        highlightPlayer(turnReport.turnReport)
}

function setScores(scores) {
        if (scores.length !== 2)
                return
        playerOneScore.updateScore(scores[0])
        playerTwoScore.updateScore(scores[1])
}

function setStatistics(stats) {
        if (stats.length !== 2)
                return
        playerOneStats.setValues(stats[0])
        playerTwoStats.setValues(stats[1])
}

function highlightPlayer(turnInfo) {
        const playerNumber = turnInfo.currentPlayerNumber
        if (playerNumber === 0)
                highlight(playerOne, playerTwo, playerOneInfo, playerTwoInfo, turnInfo.playerTurn)
        else if (playerNumber === 1)
                highlight(playerTwo, playerOne, playerTwoInfo, playerOneInfo, turnInfo.playerTurn)
        else
                throw "INVALID PLAYER NUMBER!"
}

function highlight(p1, p2, p3, p4, playerTurn) {
        p1.color = "blue"
        p2.color = "green"
        p3.hideDarts(playerTurn)
        p4.hideDarts(3)
}
