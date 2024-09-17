function initFromIndex(index) {
    const data = dataModel.get(index)
    const gameMode = data.mode
    const gameScore = data.score
    init(gameMode, gameScore)
}

function init(gameMode, gameScore) {
    const obj = toObject(gameMode, gameScore)
    const json = JSON.stringify(obj)
    dartsInitializer.init(json)
    requestTournamentPage()
}

function toObject(mode, gameScore) {
    return {
        "playersCount": 2,
        "gameMode": mode,
        "initialScore": Number.parseInt(gameScore)
    }
}
