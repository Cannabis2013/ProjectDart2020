function openConfirmDialog(text,acceptSlot){
    const modalObj = createDialog("confirmation/DialogConfirm.qml", tournamentPage)
    modalObj.accepted.connect(acceptSlot)
    modalObj.text = text
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
