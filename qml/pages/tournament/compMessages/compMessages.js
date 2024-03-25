function updateMessages() {
        updateTargetMessage()
        updateDiffMessage()
}

function updateTargetMessage() {
        const row = dartsScores.finishRow()
        if (row.length > 0)
                showTargetMessage(row)
        else
                hideTargetMessage()
}

function showTargetMessage(row) {
        finishRow.message = row
        finishRow.visible = true
}

function hideTargetMessage() {
        finishRow.visible = false
        finishRow.message = ""
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
