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
    const playerNumber = dartsTurns.playerNumber()
    if (playerNumber === 0) {
        playerOne.color = "blue"
        playerTwo.color = "green"
    } else if (playerNumber === 1) {
        playerOne.color = "green"
        playerTwo.color = "blue"
    } else
        throw "INVALID PLAYER NUMBER!"
}
