function openRestartDialog(acceptSlot) {
        const modalObj = createDialog("restart/DialogRestart.qml", tournamentPage)
        modalObj.accepted.connect(acceptSlot)
        modalObj.open()
}

function openQuitDialog(acceptSlot) {
        const modalObj = createDialog("quit/DialogQuit.qml", tournamentPage)
        modalObj.accepted.connect(acceptSlot)
        modalObj.open()
}

function openWinnerDialog(restartSlot, undoSlot) {
        const modalObj = createDialog("winner/DialogWinner.qml", applicationWindow)
        modalObj.restartClicked.connect(restartSlot)
        modalObj.undoClicked.connect(undoSlot)
}

function createDialog(dialogUrl, parentObj) {
        const modalComp = Qt.createComponent(dialogUrl)
        return modalComp.createObject(parentObj)
}
