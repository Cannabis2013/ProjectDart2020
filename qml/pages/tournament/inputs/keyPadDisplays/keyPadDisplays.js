function add(modId, point) {
    const input = inputsDisplay.addInput(modId, point)
    if (input) {
        const multiplier = toModMultiplier(input.modId)
        const score = multiplier * point
        const updatedScore = scoreDisplay.addScore(score)
        scorePreview.updateScore(updatedScore)
    }
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

function clearInputs() {
    scoreDisplay.clear()
    inputsDisplay.clear()
    scorePreview.clear()
}
