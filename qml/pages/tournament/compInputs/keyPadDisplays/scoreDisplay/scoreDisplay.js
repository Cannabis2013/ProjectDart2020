function add(modId, point) {
        const score = calcScore(modId, point)
        const scoreText = textScore.text
        const currentScore = scoreText == "" ? 0 : Number.parseInt(scoreText)
        const newScore = currentScore + score
        textScore.text = newScore
        return newScore
}

function subtract(modId, point) {
        const score = calcScore(modId, point)
        const newScore = subtractedScore(score)
        textScore.text = newScore
        return newScore
}

function subtractedScore(score) {
        const current = Number.parseInt(textScore.text)
        return current - score
}

function calcScore(modId, point) {
        const multiplier = modMultiplier(modId)
        return multiplier * point
}

function modMultiplier(modId) {
        if (modId === "S")
                return 1
        if (modId === "D")
                return 2
        if (modId === "T")
                return 3
        return -1
}

function clear() {
        textScore.text = ""
}
