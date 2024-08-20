function add(score) {
    const scoreText = textScore.text
    const currentScore = scoreText == "" ? 0 : Number.parseInt(scoreText)
    const newScore = currentScore + score
    textScore.text = newScore
    return newScore
}

function subtract(score) {
    const current = Number.parseInt(textScore.text)
    const newScore = current - score
    textScore.text = newScore
    return newScore
}
