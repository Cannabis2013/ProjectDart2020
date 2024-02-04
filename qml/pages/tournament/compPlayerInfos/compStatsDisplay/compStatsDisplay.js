function setValues(statistics) {
        averageText.text = formatted("Average", statistics.average)
        lowText.text = formatted("Low", statistics.low)
        highText.text = formatted("High", statistics.high)
        totalText.text = formatted("Hits", statistics.throwCount)
}

function formatted(title, value) {
        return `${title}\n${value}`
}
