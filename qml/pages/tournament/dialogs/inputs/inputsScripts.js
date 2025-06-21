.import "../../../../utils/nameUtils.js" as Names

function init() {
  const player = JSON.parse(dartsPlayers.current())
  playerName.text = Names.shortenName(player.name)
  const inputs = dartsInputs.inputs(player.name)
  const json = JSON.parse(inputs)
  for (var i = 0; i < json.length; i++) {
    const input = json[i]
    inputsModel.append(createElement(input))
  }
}

function createElement(input) {
  return {
    "round": input.roundIndex,
    "value": `${input.mod} ${input.point}`
  }
}
