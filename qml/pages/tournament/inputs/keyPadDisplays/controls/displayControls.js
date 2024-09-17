function removeOne() {
    if (!inputsDisplay.hasInputs())
        return
    const input = inputsDisplay.popInput()
    const updatedScore = updateScoreDisplay(input)
    scorePreview.updateScore(updatedScore)
}

function updateScoreDisplay(input) {
    const multiplier = toModMultiplier(input.modId)
    const point = input.point
    const score = multiplier * point
    return scoreDisplay.subtractScore(score)
}

function clearInputs() {
    scoreDisplay.clear()
    inputsDisplay.clear()
    scorePreview.clear()
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
