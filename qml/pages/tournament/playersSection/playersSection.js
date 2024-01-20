function setPlayers(names) {
        for (var i = 0; i < names.length; i++) {
                const name = names[i]
                const playerRect = playerRects.children[i]
                playerRect.setPlayerName(name)
        }
}

function highlightRect(name, turnIndex) {
        if (playerOne.name === name)
                highlightPlayerOne(turnIndex)
        else if (playerTwo.name === name)
                highlightPlayerTwo(turnIndex)
}

function highlightPlayerOne(turnIndex) {
        playerOne.highlight(true,turnIndex)
        playerTwo.highlight(false)
}

function highlightPlayerTwo(turnIndex) {
        playerTwo.highlight(true,turnIndex)
        playerOne.highlight(false)
}
