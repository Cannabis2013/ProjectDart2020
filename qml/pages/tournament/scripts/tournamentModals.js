function openWinnerModal(playerDetails, statisticDetails, restartSlot, undoSlot) {
        const modalComp = Qt.createComponent("../modals/WinnerModal.qml")
        const modalObj = modalComp.createObject(tournamentPage)
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

function openRestartModal(acceptSlot) {
        const modalObj = createDefaultModal(acceptSlot)
        modalObj.text = "Sure you want to restart?"
        modalObj.open()
}

function openBackModal(acceptSlot) {
        const modalObj = createDefaultModal(acceptSlot)
        modalObj.text = "Sure you want to exit?\n(Your state is saved)"
        modalObj.open()
}

function createDefaultModal(acceptSlot) {
        const modalComp = Qt.createComponent("../modals/TextModal.qml")
        const modalObj = modalComp.createObject(tournamentPage)
        modalObj.accepted.connect(acceptSlot)
        return modalObj
}
