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
        const input = createInput(modId, point)
        inputsMem.push(input)
        updateDisplay()
        updateScore(input)
}

function createInput(modId, point) {
        return {
                "modId": modId,
                "point": point
        }
}

function updateDisplay() {
        let text = ""
        inputsMem.forEach(input => text += `${input.modId}${input.point} `)
        textDisplay.inputsText = text
}

function clearInputs() {
        textDisplay.inputsText = ""
        textDisplay.scoreText = ""
        inputsMem = []
}

function updateScore(input) {
        const m = multiplier(input.modId)
        const score = m * input.point
        const text = textDisplay.scoreText
        const currentScore = text === "" ? 0 : Number.parseInt(text)
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
