.import "gameModes.js" as GameModes

function init(gameMode, gameScore) {
        const obj = toObject(gameMode, gameScore)
        const json = JSON.stringify(obj)
        dartsInitializer.init(json)
        requestTournamentPage()
}

function toObject(mode, gameScore) {
        const obj = {
                "playersCount": 2,
                "gameMode": mode,
                "initialScore": Number.parseInt(gameScore)
        }
        return obj
}

function initFlickable() {
        const modes = GameModes.gameModes()
        const totalHeight = modes.length * (128 + 6)
        flickable.contentHeight = totalHeight
        flickableContent.height = totalHeight
        modes.forEach(mode => createFromMode(mode))
}

function createFromMode(mode) {
        const obj = Qt.createComponent("GameStyleRect.qml")
        const comp = obj.createObject(flickableContent)
        comp.initialScore = mode.score
        comp.title = mode.modeTitle
        comp.mode = mode.mode
        comp.description = mode.modeDescription
}
