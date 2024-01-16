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
        const modalComp = Qt.createComponent("TextModal.qml")
        const modalObj = modalComp.createObject(tournamentPage)
        modalObj.accepted.connect(acceptSlot)
        return modalObj
}
