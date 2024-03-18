function initValues() {
        const turnReport = JSON.parse(dartsPlayers.winnerInfo())
        winnerText.text = turnReport.winnerName
        animatedImage.source = turnReport.winnerImage
}
