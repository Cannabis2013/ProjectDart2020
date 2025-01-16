function setValues(statsInfo) {
    averageText.text = formatted("MID", statsInfo.average)
    lowText.text = formatted("MIN", statsInfo.low)
    highText.text = formatted("MAX", statsInfo.high)
    totalText.text = formatted("HIT", statsInfo.throwCount)
}

function formatted(title, value) {
    return `${title}\n${value}`
}
