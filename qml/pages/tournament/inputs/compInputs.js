.import "../dialogs/dialogs.js" as Dialogs

function handleInput(modId, point) {
    const score = inputsDisplay.addInput(modId, point)
}

function reset() {
    inputsDisplay.flushInputs()
}

function report() {
    const inputs = inputsDisplay.readInputs()
    if (inputs.length <= 0)
        Dialogs.openConfirmDialog("Sure?", performReport)
    else
        performReport(inputs)
}

function performReport(inputs = []) {
    reportScores(inputs)
    inputsDisplay.flushInputs()
}
