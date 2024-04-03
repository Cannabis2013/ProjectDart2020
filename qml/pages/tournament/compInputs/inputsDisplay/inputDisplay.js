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
        const newScore = scoreDisplay.addScore(modId, point)
        updatePreview(newScore)
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
        scoreDisplay.inputsText = text
}

function removeOne() {
        if (inputsMem.length <= 0)
                return
        const input = inputsMem.pop()
        updateDisplay()
        const newScore = scoreDisplay.pop(input.modId, input.point)
        updatePreview(newScore)
}

function clearInputs() {
        scoreDisplay.clear()
        inputsMem = []
        updatePreview(0)
}
