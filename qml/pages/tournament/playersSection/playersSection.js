function setPlayers(names) {
        for (var i = 0; i < names.length; i++) {
                const name = names[i]
                const playerRect = getPlayerRect(i)
                playerRect.setPlayerName(name)
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
        turnRect.x = centerXOf(playerOne)
}

function highlightPlayerTwo(turnIndex) {
        playerTwo.highlight(true, turnIndex)
        playerOne.highlight(false)
        turnRect.x = centerXOf(playerTwo)
}

function centerXOf(object) {
        const circleCenterX = turnRect.width / 2
        const objectCenterX = object.x + object.width / 2
        return objectCenterX - circleCenterX
}
