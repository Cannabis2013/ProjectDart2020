function openWinnerModal(playerDetails, statisticDetails, restartSlot, undoSlot) {
        const modalComp = Qt.createComponent("WinnerModal.qml")
        const modalObj = modalComp.createObject(applicationWindow)
        modalObj.restartClicked.connect(restartSlot)
        modalObj.undoClicked.connect(undoSlot)
        updatePlayerDetails(modalObj, playerDetails)
        modalObj.setStatisticsDetails(statisticDetails)
}

function updatePlayerDetails(modalObj, playerDetails) {
        const name = playerDetails.winnerName
        const url = playerDetails.winnerImage
        modalObj.setPlayerDetails(name, url)
}

function setStatistics(arr) {
        for (var index = 0; index < arr.length; index++) {
                const stats = arr[index]
                statisticsSection.setPlayerName(index, stats.name)
                statisticsSection.setPlayerStatistic(index, stats)
        }
}

function setPlayerDetails(name, url) {
        winnerSection.setWinnerUrl(url)
        winnerSection.setWinnerName(name)
}
