.import "../dialogs/dialogs.js" as Dialogs

var inputsMem = []

function readInputs() {
  return inputsMem
}

function updateDisplay(modId, point) {
  if (inputsMem.length >= 3)
    return
  const input = {
    "modId": modId,
    "point": point
  }
  inputsMem.push(input)
  inputsDisplay.update(inputsMem)
  reportPreview(inputsMem)
}

function report() {
  if (inputsMem.length <= 0)
    Dialogs.openConfirmDialog("Sure?", performReport)
  else
    performReport()
}

function performReport() {
  reportInputs(inputsMem)
  flushInputs()
}

function popInput() {
  if (inputsMem.length <= 0)
    return undefined
  const input = inputsMem.pop()
  inputsDisplay.update(inputsMem)
  reportPreview(inputsMem)
}

function flushInputs() {
  inputsMem = []
  inputsDisplay.update()
  reportPreview(inputsMem)
}
