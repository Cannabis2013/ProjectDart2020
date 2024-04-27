function add(modId, point) {
        const input = inputsDisplay.addInput(modId, point)
        if (input) {
                const score = toScore(modId, point)
                const updatedScore = scoreDisplay.addScore(score)
                scorePreview.updateScore(updatedScore)
        }
}

function removeOne() {
        if (!inputsDisplay.hasInputs())
                return
        const input = inputsDisplay.popInput()
        const score = toScore(input.modId, input.point)
        const updatedScore = scoreDisplay.subtrackScore(score)
        scorePreview.updateScore(updatedScore)
}

function clearInputs() {
        scoreDisplay.clear()
        inputsDisplay.clear()
        scorePreview.clear()
}

function toScore(modId, point) {
        const multiplier = toModMultiplier(modId)
        return multiplier * point
}

function toModMultiplier(modId) {
        if (modId === "S")
                return 1
        if (modId === "D")
                return 2
        if (modId === "T")
                return 3
        return -1
}
