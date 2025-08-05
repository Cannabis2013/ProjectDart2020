.import "dialogs/dialogs.js" as Dialogs

let inputs = []

function handleCloseEvent(event) {
  if (event.key === Qt.Key_Back) {
    event.accepted = true
    Dialogs.openQuitDialog(menuRequest)
  }
}

function isPortrait() {
  return tournamentPage.height >= tournamentPage.width
}

function restartGame() {
  dartsInitializer.reset()
  updateTurnValues()
  tournamentPage.forceActiveFocus()
}

function undo() {
  dartsTurns.undo()
  updateTurnValues()
  tournamentPage.forceActiveFocus()
}

function redo() {
  dartsTurns.redo()
  updateTurnValues()
}

function reportInputs() {
  if (inputs.length === 0)
    Dialogs.openConfirmDialog("Sikker?", performReport)
  else
    performReport()
}

function performReport() {
  const json = JSON.stringify(inputs)
  dartsInputs.add(json)
  updateTurnValues()
}

function updateTurnValues() {
  if (dartsPlayers.isWinnerFound()) {
    Dialogs.openWinnerDialog(restartGame, undo)
    return
  }

  scoreDisplay.update()
  turnControls.update()
  messageSection.update()
  flush()
}

function addInput(modId, point) {
  if (inputs.length > 2)
    return

  inputs.push({
                "modId": modId,
                "point": point
              })

  const sum = inputsScore(inputs)
  inputDisplay.update(inputs, sum)
  scoreDisplay.subtract(sum)
}

function inputsScore(inputs) {
  let sum = 0
  let input = null
  for (var i = 0; i < inputs.length; i++) {
    input = inputs[i]
    sum += scoreValue(input.modId, input.point)
  }
  return sum
}

function scoreValue(modId, point) {
  if (modId === "T")
    return 3 * point
  else if (modId === "D")
    return 2 * point
  else
    return point
}

function pop() {
  inputs.pop()
  const sum = inputsScore(inputs)
  scoreDisplay.subtract(sum)
  inputDisplay.update(inputs, sum)
}

function flush() {
  inputs = []
  inputDisplay.update(inputs, 0)
  scoreDisplay.subtract(0)
}
