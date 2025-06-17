function init() {
  const values = {
    "playersCount": parseInt(playersCountSelector.current),
    "initialScore": parseInt(initialScoreSelector.current),
    "withOpeningCondition": openingSelector.current != "None",
    "withCloseCondition": closeningSelector.current != "None",
    "openingModifier": openingSelector.current
  }

  dartsInitializer.init(JSON.stringify(values))
}
