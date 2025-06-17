function open(playerName) {
  const comp = Qt.createComponent("InfoDialog.qml")
  const dialog = comp.createObject(applicationWindow, {
                                     "playerName": playerName
                                   })
  dialog.open()
}

function init() {
  const inputs = dartsInputs.inputs(playerName)
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
