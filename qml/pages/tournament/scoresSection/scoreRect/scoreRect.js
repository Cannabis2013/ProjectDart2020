function highlight(status, count) {
        if (status) {
                playerInfo.showCounter(true)
                playerInfo.updateVisibleDarts(count)
                playersScoreRect.color = "blue"
        } else {
                playerInfo.showCounter(false)
                playersScoreRect.color = "green"
        }
}
