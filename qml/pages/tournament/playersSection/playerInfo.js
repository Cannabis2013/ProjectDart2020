function setPlayer(player) {
        playerInfo.id = player.name
        playerName.text = shortenName(player.name)
        playerNationality.text = `Nationality: ${player.nationality}`
}

function shortenName(name) {
        if (name.length < 12)
                return name
        const formatted = formatName(name)
        if (formatted.length > 16)
                return formatted.substring(0, 14) + ".."
        return formatted
}

function formatName(name) {
        const found = assertName(name)
        if (found.length === 1)
                return reduceLastName(name) // Has only  a lastname
        else if (found.length > 1)
                return reduceMiddleNames(name) // Has middlename(s)
        else
                return name
}

function assertName(name) {
        const reg = /\s[A-z]*/g
        return name.match(reg)
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

function highlight(status, count) {
        infoRect.color = status ? "blue" : "green"
        dartsCounter.hideDarts(status ? count : 3)
}
