function handleInput(modId, point) {
        inputsDisplay.addInput(modId, point)
}

function report() {
        const inputs = inputsDisplay.readInputs()
        reportScores(inputs)
        inputsDisplay.flushInputs()
}
