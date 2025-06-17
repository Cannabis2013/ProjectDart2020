function init() {
  const values = {
    "playersCount": parseInt(playersCountSelector.current),
    "initialScore": parseInt(initialScoreSelector.current),
    "withOpenCondition": openingSelector.current != "None",
    "withCloseCondition": closeningSelector.current != "None",
    "openingModifier": toModifierId(openingSelector.current)
  }
  dartsInitializer.init(JSON.stringify(values))
}

function toModifierId(modName) {
  if (modName === "tripple")
    return "T"
  if (modName === "double")
    return "D"
  return "S"
}
