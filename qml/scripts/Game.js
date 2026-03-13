function handleCloseEvent(event) {
  if (event.key === Qt.BackButton) {
    event.accepted = true;
    tournamentPage.menuRequest();
  }
}

function isPortrait() {
  return tournamentPage.height > tournamentPage.width;
}

function restartGame() {
  dialogLoader.sourceComponent = null
  restartDialog.visible = false;
  dartsInitializer.reset();
  update();
}

function undo() {
  dartsTurns.undo();
  update();
}

function redo() {
  dartsTurns.redo();
  update();
}

function reportInputs() {
  if (inputs.all.length === 0)
    proceedDialog.visible = true;
  else{
    saveInputs()
    update()
  }
}

function saveInputs(){
  const json = JSON.stringify(inputs.all)
  dartsInputs.add(json)
}

function update() {
  dartsInitializer.saveState()
  if (winnerInfo.isWinnerFound()) {
    dialogLoader.sourceComponent = winnerScreen;
    return;
  }
  inputs.all = []
  backgroundAnimation.running = false
  updateDisplays()
}

function updateDisplays(){
  scoreDisplay.update(inputs.all)
  finishDisplay.update(inputs.all)
  inputsDisplay.update(inputs.all)
  statsDisplay.update()
  turnControls.update()
}

function addInput(modId, point) {
  if (inputs.all.length > 2)
    return;
  inputs.all.push({
    "modId": modId,
    "point": point
  });

  backgroundAnimation.running = true
  inputsDisplay.update(inputs.all)
  finishDisplay.update(inputs.all)
  scoreDisplay.update(inputs.all);
}

function popInput() {
  inputs.all.pop();
  updateDisplays()
}
