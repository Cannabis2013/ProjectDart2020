
function updateMessages() {
        const row = dartsScores.finishRow()
        const delta = dartsScores.delta()
        if (row.length > 0)
                showTargetMessage(row)
        else
                hideTargetMessage()
        scoreSpan.message = delta
}

function showTargetMessage(row) {
        finishRow.message = row
        finishRow.visible = true
}

function hideTargetMessage() {
        finishRow.visible = false
        finishRow.message = ""
}
