function initFromIndex(index) {
  print("Init")
  const data = dataModel.get(index)
  const gameMode = data.mode
  const gameScore = data.score
  init(gameMode, gameScore)
}

function init(gameMode, gameScore) {
  const obj = {
    "playersCount": 2,
    "gameMode": gameMode,
    "initialScore": Number.parseInt(gameScore)
  }
  const json = JSON.stringify(obj)
  dartsInitializer.init(json)
  requestTournamentPage()
}
