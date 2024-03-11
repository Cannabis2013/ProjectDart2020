function setValues(jsonReport) {
        setScores(jsonReport.scoresReport)
        setStatistics(jsonReport.statsReport)
}

function setScores(jsonReport) {
        const scores = jsonReport.scores
        if (scores.length !== 2)
                return
        playerOneItem.setScore(scores[0])
        playerTwoItem.setScore(scores[1])
}

function setStatistics(statsReport) {
        if (statsReport.length !== 2)
                return
        playerOneItem.setStatistics(statsReport[0])
        playerTwoItem.setStatistics(statsReport[1])
}
