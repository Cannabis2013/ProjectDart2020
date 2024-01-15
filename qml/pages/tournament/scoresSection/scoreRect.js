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

function updateStatistics(statistics) {
        playerStatistics.updateStatistics(statistics)
}
