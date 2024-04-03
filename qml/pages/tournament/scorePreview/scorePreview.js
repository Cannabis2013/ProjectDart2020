function show(score) {
        if (score <= 0) {
                hidePreview()
                return
        }
        const remaining = dartsScores.currentRemaining()
        const remaingPreview = remaining - score
        textPreview.text = remaingPreview > 0 ? remaingPreview : 0
        opacity = 0.9
}

function hidePreview() {
        textPreview.text = ""
        opacity = 0
}
