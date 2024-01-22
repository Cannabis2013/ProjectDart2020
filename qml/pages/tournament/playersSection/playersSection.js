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
        turnPointer.x = centerXOf(playerOne)
}

function highlightPlayerTwo(turnIndex) {
        playerTwo.highlight(true, turnIndex)
        playerOne.highlight(false)
        turnPointer.x = centerXOf(playerTwo)
}

function centerXOf(object) {
        const circleCenterX = turnPointer.width / 2
        const objectCenterX = object.x + object.width / 2
        return objectCenterX - circleCenterX
}
