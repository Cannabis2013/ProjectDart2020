function handleInput(modId, point) {
        const score = inputsDisplay.addInput(modId, point)
}

function reset() {
        inputsDisplay.flushInputs()
}

function report() {
        const inputs = inputsDisplay.readInputs()
        reportScores(inputs)
        inputsDisplay.flushInputs()
}
