function winnerModeDialog(parentId,qmlSignal) {
        const component = Qt.createComponent("OptionsDialog.qml")
        const dialog = component.createObject(parentId)
        dialog.optionClicked.connect(qmlSignal)
        dialog.open()
}
