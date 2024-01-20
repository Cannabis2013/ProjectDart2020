function setPlayer(player) {
        playerName.text = shortenName(player.playerName)
}

function shortenName(name) {
        if (name.length > 16)
                return name.substring(0, 16) + ".."
        return name
}

function highlight(status, count) {
        infoRect.color = status ? "blue" : "green"
        dartsCounter.setVisibleDarts(status ? count : 3)
}
