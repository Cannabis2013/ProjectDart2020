function setStatistics(index, statistics) {
        const text = toString(statistics)
        if (index === 0)
                playerOneStats.text = text
        else
                playerTwoStats.text = text
}

function toString(statistics) {
        const average = statistics.average
        const low = statistics.low
        const high = statistics.high
        const throwCount = statistics.throwCount
        return `Average: ${average}\nLow: ${low}\nHigh: ${high}\nHits: ${throwCount}`
}

function setPlayer(index, name) {
        if (index === 0)
                playerOne.text = name
        else
                playerTwo.text = name
}
