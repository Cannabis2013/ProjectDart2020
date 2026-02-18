import QtQuick 6.0

Item {
  function update(inputs){
    let text = ""
    inputs.forEach(input => text += `${input.modId}${input.point} `)
    const sum = calculateSum(inputs)
    scoreBox.text = inputs.length > 0 ? `Score\n${sum}` : "Score"
    inputsBox.text = inputs.length > 0 ? `Inputs\n${text}` : "Inputs"
  }

  function calculateSum(inputs) {
    let sum = 0
    let input = null
    for (var i = 0; i < inputs.length; i++) {
      input = inputs[i];
      if (input.modId === "T")
        sum += 3 * input.point
      else if (input.modId === "D")
        sum += 2 * input.point
      else
        sum += input.point
    }
    return sum
  }

  Text {
    id: inputsBox
    anchors {
      verticalCenter: parent.verticalCenter
      left: parent.left
    }
    height: 64
    width: parent.width / 2
    lineHeight: 32
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 32
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
  }
  Text {
    id: scoreBox
    anchors {
      right: parent.right
      verticalCenter: parent.verticalCenter
    }
    height: 64
    width: parent.width / 2
    lineHeight: 32
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 32
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
  }
}
