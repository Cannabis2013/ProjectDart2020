function highlight(status, count) {
        if (status) {
                playerInfo.counterVisible = true
                playerInfo.dartsCount = count
                playersScoreRect.color = "blue"
        } else {
                playerInfo.counterVisible = false
                playersScoreRect.color = "green"
        }
}

function updateStatistics(statisticValues) {
        playerStatistics.low = statisticValues.low
        playerStatistics.high = statisticValues.high
        playerStatistics.average = statisticValues.average
        playerStatistics.throwCount = statisticValues.throwCount
}
