function clearPreview() {
        textPreview.text = ""
}

function updateScorePreview(score) {
        if (score > 0)
                textPreview.text = projectedRemaining(score)
        else
                clearPreview()
}

function projectedRemaining(score) {
        const remaining = dartsScores.currentRemaining()
        const remaing = remaining - score
        return remaing > 0 ? remaing : 0
}
