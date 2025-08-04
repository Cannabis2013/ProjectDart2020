.import "dialogs/dialogs.js" as Dialogs

function handleCloseEvent(event) {
  if (event.key === Qt.Key_Back) {
    event.accepted = true
    Dialogs.openQuitDialog(menuRequest)
  }
}

function isPortrait() {
  return tournamentPage.height > tournamentPage.width
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
  if (inputDisplay.inputs().length === 0)
    Dialogs.openConfirmDialog("Sikker?", performReport)
  else
    performReport()
}

function performReport() {
  const json = JSON.stringify(inputDisplay.inputs())
  dartsInputs.add(json)
  updateTurnValues()
}

function updateTurnValues() {
  if (dartsPlayers.isWinnerFound()) {
    Dialogs.openWinnerDialog(restartGame, undo)
    return
  }

  playerInfo.update()
  turnControls.update()
  messageSection.update()
  inputDisplay.reset()
}

function updateSections() {}

function handleInput(modId, point) {
  if (inputMem.inputs.length >= 3)
    return
  inputMem.inputs.push({
                         "modId": modId,
                         "point": point
                       })
  inputDisplay.update(inputMem.inputs)
}
