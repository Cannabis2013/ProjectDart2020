function setPlayers(players) {
        for (var i = 0; i < players.length; i++) {
                const player = players[i]
                const playerRect = getPlayerRect(i)
                playerRect.setPlayer(player)
        }
}

function getPlayerRect(index) {
        if (index === 0)
                return playerOne
        else
                return playerTwo
}

function highlightRect(name, turnIndex) {
        if (playerOne.name === name)
                highlightPlayerOne(turnIndex)
        else if (playerTwo.name === name)
                highlightPlayerTwo(turnIndex)
}

function highlightPlayerOne(turnIndex) {
        playerOne.highlight(true, turnIndex)
        playerTwo.highlight(false)
}

function highlightPlayerTwo(turnIndex) {
        playerTwo.highlight(true, turnIndex)
        playerOne.highlight(false)
}
