function init() {
        initPlayers()
        initScores()
}

function initPlayers() {
        const playerOne = JSON.parse(dartsPlayers.playerOne())
        const playerTwo = JSON.parse(dartsPlayers.playerTwo())
        playerOneInfo.setPlayer(playerOne)
        playerTwoInfo.setPlayer(playerTwo)
}

function initScores() {
        const oneScore = dartsScores.playerOne()
        const twoScore = dartsScores.playerTwo()
        playerOneScore.initScore(oneScore)
        playerTwoScore.initScore(twoScore)
}

function updateValues() {
        updateScores()
        updateStatistics()
        highlightPlayer()
}

function updateScores() {
        const oneScore = dartsScores.playerOne()
        const twoScore = dartsScores.playerTwo()
        playerOneScore.updateScore(oneScore)
        playerTwoScore.updateScore(twoScore)
}

function updateStatistics() {
        const oneStats = JSON.parse(dartsStats.playerOne())
        const twoStats = JSON.parse(dartsStats.playerTwo())
        playerOneStats.setValues(oneStats)
        playerTwoStats.setValues(twoStats)
}

function highlightPlayer() {
        const playerTurn = dartsTurns.turnNumber()
        const playerNumber = dartsTurns.playerNumber()
        if (playerNumber === 0)
                highlight(playerOne, playerTwo, playerOneInfo, playerTwoInfo, playerTurn)
        else if (playerNumber === 1)
                highlight(playerTwo, playerOne, playerTwoInfo, playerOneInfo, playerTurn)
        else
                throw "INVALID PLAYER NUMBER!"
}

function highlight(p1, p2, p3, p4, playerTurn) {
        p1.color = "blue"
        p2.color = "green"
        p3.hideDarts(playerTurn)
        p4.hideDarts(3)
}
