function updateMessages() {
  updateTargetMessage()
}

function updateTargetMessage() {
  const row = dartsScores.finishRow()
  finishRow.message = row.length > 0 ? row : ""
  finishRow.visible = row.length > 0
}
