function handleCloseEvent(event) {
        if (event.key === Qt.Key_Back) {
                event.accepted = true
                Modals.openBackModal(menuRequest)
        }
}

function isPortrait() {
        return tournamentPage.height > tournamentPage.width
}
