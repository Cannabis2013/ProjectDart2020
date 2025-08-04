function addInput(modId, point) {
  if (inputMem.inputs.length > 2)
    return
  inputMem.inputs.push({
                         "modId": modId,
                         "point": point
                       })
  updateDisplays()
}

function updateDisplays() {
  let text = ""
  const inputs = inputMem.inputs
  inputs.forEach(input => text += `${input.modId}${input.point} `)
  inputsBox.value = text

  let sum = 0
  let input = null
  for (var i = 0; i < inputs.length; i++) {
    input = inputs[i]
    sum += scoreValue(input.modId, input.point)
  }
  scoreBox.value = sum

  const preview = inputMem.initialScore - sum
  scorePreview.value = preview > 0 ? preview : 0
}

function scoreValue(modId, point) {
  if (modId === "T")
    return 3 * point
  else if (modId === "D")
    return 2 * point
  else
    return point
}

function pop() {
  inputMem.inputs.pop()
  updateDisplays()
}

function reset() {
  inputMem.initialScore = dartsScores.current()
  inputMem.inputs = []
  updateDisplays()
}
