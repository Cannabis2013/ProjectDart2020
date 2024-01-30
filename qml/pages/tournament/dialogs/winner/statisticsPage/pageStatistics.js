function setStatistics(statistics) {
        if (statistics.length !== 2)
                return
        setPlayerOneStats(statistics[0])
        setPlayerTwoStats(statistics[1])
}

function setPlayerOneStats(statistics) {
        playerOne.text = statistics.name
        playerOneStats.text = toString(statistics)
}

function setPlayerTwoStats(statistics) {
        playerTwo.text = statistics.name
        playerTwoStats.text = toString(statistics)
}

function toString(statistics) {
        const average = statistics.average
        const low = statistics.low
        const high = statistics.high
        const throwCount = statistics.throwCount
        return `Average: ${average}\nLow: ${low}\nHigh: ${high}\nHits: ${throwCount}`
}
