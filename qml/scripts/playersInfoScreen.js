.import "nameUtils.js" as Names

function updateName(name,nameObj,remainingObj){
  nameObj.text = Names.shortenName(name, 9)
  remainingObj.text = dartsScores.remaining(name)
  const indexes = JSON.parse(dartsTurns.indexes())
  const currentRoundIndex = indexes.roundIndex
  let inputs = []
  let inputsAsString = ""
  for (let roundIndex = 1; roundIndex <= currentRoundIndex; roundIndex++) {
    inputs = JSON.parse(dartsInputs.inputs(name,roundIndex))
    if(inputs.length <= 0) continue
    inputsAsString = inputs.reduce((s,input) => s + `${input.mod}${input.point} `,"")
    inputsModel.append({"value": `Round ${roundIndex}: ${inputsAsString}`})
  }
}

function init(){
  playersInfo.players = dartsPlayers.all()
  inputsListRepeater.model = playersInfo.players.length
  const current = dartsPlayers.current()
  const playerIndex = dartsPlayers.playerIndex(current)
  playersSwipeView.setCurrentIndex((inputsListRepeater.count - 1) - playerIndex)
}
