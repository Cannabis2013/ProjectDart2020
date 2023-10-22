function startGame() {
        const mode = winnerSelector.selectedValue
        const names = playerNamesList.playerNames
        if (names.length > 0) {
                dartsController.init(names, mode)
                requestTournamentPage()
        }
}
