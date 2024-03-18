function setScore(score) {
        playerScore.text = score
}

function setStatistics(statistics) {
        playerName.text = statistics.name
        playerStats.text = toString(statistics)
}

function toString(statistics) {
        const average = statistics.average
        const low = statistics.low
        const high = statistics.high
        const throwCount = statistics.throwCount
        return `Average: ${average}\nLow: ${low}\nHigh: ${high}\nHits: ${throwCount}`
}
