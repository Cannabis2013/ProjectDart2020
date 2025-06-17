function init() {
  const json = {
    "playersCount": parseInt(playersCountSelector.current),
    "initialScore": parseInt(initialScoreSelector),
    "withOpeningCondition": openingSelector.current != "None",
    "withCloseCondition": closeningSelector.current != "None",
    "openingModifier": openingSelector.current
  }

  dartsInitializer.init(json)
}
