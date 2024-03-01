function setValues(jsonReport) {
        setScores(jsonReport)
        setStatistics(jsonReport)
}

function setScores(jsonReport) {
        const scores = jsonReport.scores
        if (scores.length !== 2)
                return
        playerOneItem.setScore(scores[0])
        playerTwoItem.setScore(scores[1])
}

function setStatistics(jsonReport) {
        const statsInfo = jsonReportstatsReport
        if (statsInfo.length !== 2)
                return
        playerOneItem.setStatistics(statsInfo[0])
        playerTwoItem.setStatistics(statsInfo[1])
}
