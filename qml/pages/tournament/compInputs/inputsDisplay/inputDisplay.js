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

function removeOne() {
        if (inputsMem.length <= 0)
                return
        const input = inputsMem.pop()
        const score = calcScore(input.modId, input.point)
        const current = Number.parseInt(textDisplay.scoreText)
        if (current <= 0)
                return
        textDisplay.scoreText = current - score
        updateDisplay()
}

function clearInputs() {
        textDisplay.inputsText = ""
        textDisplay.scoreText = ""
        inputsMem = []
}

function updateScore(input) {
        const score = calcScore(input.modId, input.point)
        const text = textDisplay.scoreText
        const currentScore = text === "" ? 0 : Number.parseInt(text)
        textDisplay.scoreText = currentScore + score
}

function calcScore(modId, point) {
        const m = multiplier(modId)
        return m * point
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
