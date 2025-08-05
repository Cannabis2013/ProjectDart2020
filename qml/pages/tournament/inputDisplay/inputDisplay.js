function updateDisplays(inputs, inputsScore) {
  let text = ""
  inputs.forEach(input => text += `${input.modId}${input.point} `)
  inputsBox.value = text

  scoreBox.value = inputsScore
}
