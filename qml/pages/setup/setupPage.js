function init(mode, initialScore) {
        const obj = players(mode, initialScore)
        const json = JSON.stringify(obj)
        dartsController.init(json)
        requestTournamentPage()
}

function players(mode, initialScore) {
        const obj = {
                "players": [{
                                "name": "Snake Bite",
                                "winnerImage": "qrc:/pictures/Ressources/Pictures/SnakeBite.png"
                        }, {
                                "name": "Van Gerwin",
                                "winnerImage": "qrc:/pictures/Ressources/Pictures/winner.gif"
                        }],
                "gameMode": mode,
                "initialScore": initialScore
        }
        return obj
}
