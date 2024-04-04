function add(modId, point) {
        const input = inputsDisplay.addInput(modId, point)
        if (input) {
                const score = scoreDisplay.addScore(input.modId, input.point)
                scorePreview.updateScore(score)
        }
}

function removeOne() {
        const input = inputsDisplay.popInput()
        if (input) {
                const updatedScore = scoreDisplay.subtrackScore(input.modId, input.point)
                scorePreview.updateScore(updatedScore)
        }
}

function clearInputs() {
        scoreDisplay.clear()
        inputsDisplay.clear()
        scorePreview.clear()
}
