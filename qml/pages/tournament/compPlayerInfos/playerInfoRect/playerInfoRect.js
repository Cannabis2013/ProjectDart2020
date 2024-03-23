function setValues(score, stats) {
        scoreDisplayText.text = score
        if (stats)
                statsDisplay.setValues(stats)
}

function highlight(dartsCount) {
        playerInfoRect.color = "blue"
}

function unHighlight() {
        playerInfoRect.color = "green"
}

function setPlayer(player) {
        playerInfo.fullName = player.name
        playerInfo.formattedName = shortenName(player.name, 9)
        playerName.text = playerInfo.formattedName
}

function shortenName(name, limit) {
        if (name.length < limit)
                return name
        const found = name.match(/\s[A-z]*/g)
        const formatted = formatName(name, found, limit)
        if (formatted.length > limit)
                return shortenName(formatted)
        return formatted
}

function formatName(name, found, limit) {
        if (found.lenth <= 0)
                return name.substring(0, limit) + ".." // Ex.: Johnny Walke..
        else if (found.length === 1)
                return reduceLastName(name) // Has only  a lastname
        else if (found.length > 1)
                return reduceMiddleNames(name) // Has middlename(s)
        else
                return name
}

function reduceLastName(name) {
        const index = name.indexOf(" ")
        return name.substring(0, index + 2) + "."
}

function reduceMiddleNames(name) {
        const firstIndex = name.indexOf(" ")
        const lastIndex = name.lastIndexOf(" ")
        const firstName = name.substring(0, firstIndex)
        const lastName = name.substring(lastIndex, name.length)
        return firstName + lastName
}

function showFullName(show) {
        if (show)
                playerName.text = playerInfo.fullName
        else
                playerName.text = playerInfo.formattedName
}
