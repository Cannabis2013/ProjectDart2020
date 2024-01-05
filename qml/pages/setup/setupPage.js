function init(mode, initialScore) {
        const obj = players(mode, initialScore)
        const json = JSON.stringify(obj)
        dartsController.init(json)
        requestTournamentPage()
}

function players(mode, initialScore) {
        const obj = {
                "playersCount": 2,
                "gameMode": mode,
                "initialScore": initialScore
        }
        return obj
}
