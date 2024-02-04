function setValues(statsInfo) {
        averageText.text = formatted("Average", statsInfo.average)
        lowText.text = formatted("Low", statsInfo.low)
        highText.text = formatted("High", statsInfo.high)
        totalText.text = formatted("Hits", statsInfo.throwCount)
}

function formatted(title, value) {
        return `${title}\n${value}`
}
