function init() {
        const firstPlayer = JSON.parse(dartsPlayers.playerOne())
        const secondPlayer = JSON.parse(dartsPlayers.playerTwo())
        const oneScore = dartsScores.playerOne()
        const twoScore = dartsScores.playerTwo()
        playerOne.setPlayer(firstPlayer)
        playerTwo.setPlayer(secondPlayer)
        playerOne.setValues(oneScore)
        playerTwo.setValues(twoScore)
}

function updateValues() {
        updateComponents()
        highlightPlayer()
        shrinkPlayerRects()
}

function updateComponents() {
        const oneScore = dartsScores.playerOne()
        const twoScore = dartsScores.playerTwo()
        const oneStats = JSON.parse(dartsStats.playerOne())
        const twoStats = JSON.parse(dartsStats.playerTwo())
        playerOne.setValues(oneScore, oneStats)
        playerTwo.setValues(twoScore, twoStats)
}

function highlightPlayer() {
        const playerTurn = dartsTurns.turnNumber()
        const playerNumber = dartsTurns.playerNumber()
        turnCounter.setHiddenDarts(playerTurn)
        if (playerNumber === 0) {
                playerOne.color = "blue"
                playerTwo.color = "green"
        } else if (playerNumber === 1) {
                playerOne.color = "green"
                playerTwo.color = "blue"
        } else
                throw "INVALID PLAYER NUMBER!"
}

function expandPlayerOne() {
        if (playerOne.expanded) {
                shrinkPlayerRects()
        } else {
                playerOne.width = playerInfoItem.width
                playerOne.expanded = true
                playerTwo.width = 0
                turnCounter.visible = false
        }
}

function expandPlayerTwo() {
        if (playerTwo.expanded) {
                shrinkPlayerRects()
        } else {
                playerOne.width = 0
                playerTwo.expanded = true
                playerTwo.width = playerInfoItem.width
                turnCounter.visible = false
        }
}

function shrinkPlayerRects() {
        playerOne.width = playerInfoItem.width / 2
        playerTwo.width = playerInfoItem.width / 2
        playerOne.expanded = false
        playerTwo.expanded = false
        turnCounter.visible = true
}
