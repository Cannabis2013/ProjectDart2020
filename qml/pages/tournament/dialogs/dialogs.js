function openConfirmDialog(text, acceptSlot) {
  const dialog = createDialog("confirmation/DialogConfirm.qml")
  dialog.accepted.connect(acceptSlot)
  dialog.text = text
  dialog.open()
}

function openWinnerDialog(restartSlot, undoSlot) {
  const dialog = createDialog("winner/DialogWinner.qml")
  dialog.restartClicked.connect(restartSlot)
  dialog.undoClicked.connect(undoSlot)
}

function createDialog(dialogUrl) {
  const modalComp = Qt.createComponent(dialogUrl)
  return modalComp.createObject(applicationWindow)
}

function openInputsDialog() {
  const comp = Qt.createComponent("playerInfo/playersDialog.qml")
  const dialog = comp.createObject(applicationWindow)
  dialog.open()
}
