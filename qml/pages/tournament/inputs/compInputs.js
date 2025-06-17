.import "../dialogs/dialogs.js" as Dialogs

let inputsMem = []
let accepted = false

function readInputs() {
  return inputsMem
}

function updateDisplay(modId, point) {
  if (inputsMem.length >= 3)
    return
  if (dartsInputs.isValid(point, modId))
    accepted = true
  let input = {
    "modId": modId,
    "point": accepted ? point : 0
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
  accepted = false
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
