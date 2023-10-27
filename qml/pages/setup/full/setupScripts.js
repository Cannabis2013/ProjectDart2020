function startGame(mode, initialScore) {
        const names = playerNamesList.playerNames
        if (names.length > 0) {
                dartsController.init(names, mode, initialScore)
                requestTournamentPage()
        }
}
