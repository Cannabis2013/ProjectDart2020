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
  restartDialog.visible = false;
  dartsInitializer.reset();
  updateTurnValues();
}

function undo() {
  dartsTurns.undo();
  updateTurnValues();
}

function redo() {
  dartsTurns.redo();
  updateTurnValues();
}

function reportInputs() {
  if (privateData.inputs.length === 0)
    proceedDialog.visible = true;
  else
    performReport();
}

function performReport() {
  const json = JSON.stringify(privateData.inputs);
  dartsInputs.add(json);
  updateTurnValues();
}

function updateTurnValues() {
  dartsInitializer.saveState()
  if (winnerInfo.isWinnerFound()) {
    dialogLoader.sourceComponent = winnerScreen;
    return;
  }
  infoDisplay.updateFinish(privateData.inputs);
  turnControls.update();
  resetScoreDisplay();
}

function addInput(modId, point) {
  if (privateData.inputs.length > 2)
    return;
  privateData.inputs.push({
    "modId": modId,
    "point": point
  });

  const sum = totalInputScore(privateData.inputs);
  infoDisplay.updateScores(privateData.inputs, sum);
  infoDisplay.updateFinish(privateData.inputs);
  infoDisplay.subtract(sum);
}

function totalInputScore(inputs) {
  let sum = 0;
  let input = null;
  for (var i = 0; i < inputs.length; i++) {
    input = inputs[i];
    sum += scoreValue(input.modId, input.point);
  }
  return sum;
}

function scoreValue(modId, point) {
  if (modId === "T")
    return 3 * point;
  else if (modId === "D")
    return 2 * point;
  else
    return point;
}

function popInput() {
  privateData.inputs.pop();
  const sum = totalInputScore(privateData.inputs);
  infoDisplay.subtract(sum);
  infoDisplay.updateScores(privateData.inputs, sum);
  infoDisplay.updateFinish(privateData.inputs);
}

function resetScoreDisplay() {
  privateData.inputs = [];
  infoDisplay.resetAndUpdate();
  infoDisplay.updateFinish(privateData.inputs);
}
