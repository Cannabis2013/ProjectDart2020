function init() {
        playerInfo.initialZValue = infoRect.z
}

function setPlayer(player) {
        playerInfo.id = player.name
        playerName.text = shortenName(player.name, 9)
        playerNationality.text = player.nationality
}

function shortenName(name, limit) {
        if (name.length < limit)
                return name
        const found = assertName(name)
        const formatted = formatName(name, found, limit)
        if (formatted.length > limit)
                return shortenName(formatted)
        return formatted
}

function assertName(name) {
        const reg = /\s[A-z]*/g
        return name.match(reg)
}

function formatName(name, found, limit) {
        if (found.lenth <= 0)
                return reduceFirstName(name, limit) // Ex.: Johnny Walke..
        else if (found.length === 1)
                return reduceLastName(name) // Has only  a lastname
        else if (found.length > 1)
                return reduceMiddleNames(name) // Has middlename(s)
        else
                return name
}

function reduceFirstName(name, limit) {
        return name.substring(0, limit) + ".."
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

function handleSizeChangeRequest() {
        if (playerInfo.enlarged)
                shrink()
        else
                expand()
}

function expand() {
        playerInfo.enlarged = true
        infoRect.z = 2
        widthAni.from = infoRect.parent.width / 2
        widthAni.to = infoRect.parent.width
        widthAni.start()
}

function shrink() {
        playerInfo.enlarged = false
        widthAni.from = infoRect.width
        widthAni.to = infoRect.parent.width / 2
        widthAni.start()
}

function restoreZValue() {
        print("Animation finished")
        if (!playerInfo.enlarged)
                infoRect.z = playerInfo.initialZValue
}
