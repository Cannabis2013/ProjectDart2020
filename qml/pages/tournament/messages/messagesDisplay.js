function updateMessages() {
  updateTargetMessage()
  updateDiffMessage()
}

function updateTargetMessage() {
  const row = dartsScores.finishRow()
  finishRow.message = row.length > 0 ? row : ""
  finishRow.visible = row.length > 0
}

function updateDiffMessage() {
  const delta = dartsScores.delta()
  if (delta >= 0) {
    scoreSpan.imageUrl = "qrc:/pictures/Ressources/Pictures/upArrow.png"
    scoreSpan.message = delta
  } else {
    scoreSpan.imageUrl = "qrc:/pictures/Ressources/Pictures/downArrow.png"
    scoreSpan.message = Math.abs(delta)
  }
}
