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
  tournamentPage.updateTurnValues();
  tournamentPage.forceActiveFocus();
}

function undo() {
  dartsTurns.undo();
  tournamentPage.updateTurnValues();
  tournamentPage.forceActiveFocus();
}

function redo() {
  dartsTurns.redo();
  tournamentPage.updateTurnValues();
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
  if (winnerInfo.isWinnerFound()) {
    dialogLoader.sourceComponent = winnerScreen;
    return;
  }
  updateMessageComponent();
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
  updateMessageComponent();
  infoDisplay.subtract(sum);
}

function updateMessageComponent() {
  const count = privateData.inputs.length;
  const turnIndex = count > 0 ? count : 0;
  const sum = totalInputScore(privateData.inputs);
  const remaining = dartsScores.current() - sum;
  const row = dartsFinishes.finish(remaining, turnIndex);
  messageSection.update(row);
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
  updateMessageComponent();
}

function resetScoreDisplay() {
  privateData.inputs = [];
  infoDisplay.resetAndUpdate();
  updateMessageComponent();
}
