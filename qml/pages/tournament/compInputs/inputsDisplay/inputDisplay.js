var inputsMem = []

function hasInputs() {
        return inputsMem.length > 0
}

function readInputs() {
        return inputsMem
}

function addInput(modId, point) {
        if (inputsMem.length >= 3)
                return
        const input = {
                "modId": modId,
                "point": point
        }
        inputsMem.push(input)
        updateDisplay()
        updateScore(input)
}

function updateDisplay() {
        textDisplay.clear()
        let text = ""
        inputsMem.forEach(input => text += `${input.modId}${input.point} `)
        textDisplay.inputsText = text
}

function clearInputs() {
        textDisplay.clear()
        inputsMem = []
}

function updateScore(input) {
        const m = multiplier(input.modId)
        const score = m * input.point
        const currentScore = textDisplay.scoreText === "" ? 0 : Number.parseInt(textDisplay.scoreText)
        textDisplay.scoreText = currentScore + score
}

function multiplier(modId) {
        if (modId === "S")
                return 1
        if (modId === "D")
                return 2
        if (modId === "T")
                return 3
        return -1
}
