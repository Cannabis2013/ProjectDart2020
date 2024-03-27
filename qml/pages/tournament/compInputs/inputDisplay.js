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
        inputsText.text = ""
        inputsMem.forEach(input => inputsText.text += `${input.modId}${input.point} `)
}

function clearInputs() {
        inputsText.text = ""
        inputsMem = []
        scoreText.text = ""
}

function updateScore(input) {
        const m = multiplier(input.modId)
        const score = m * input.point
        const currentScore = scoreText.text === "" ? 0 : Number.parseInt(scoreText.text)
        scoreText.text = currentScore + score
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
