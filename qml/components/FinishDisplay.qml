import QtQuick 2.1

Item {
  function update(inputs) {
    const count = inputs.length
    const turnIndex = count > 0 ? count : 0
    let scoreSum = calculateSum(inputs)
    const remaining = dartsScores.current() - scoreSum
    const row = dartsFinishes.finish(remaining, turnIndex)
    finishText.text = row.length > 0 ? `Finish with\n${row}` : "Finish with"
  }
  function calculateSum(inputs) {
    let sum = 0;
    let input = null;
    for (var i = 0; i < inputs.length; i++) {
      input = inputs[i];
      if (input.modId === "T")
        sum += 3 * input.point
      else if (input.modId === "D")
        sum += 2 * input.point
      else
        sum += input.point
    }
    return sum;
  }

  Text{
    id: finishText
    anchors{
      centerIn: parent
    }
    lineHeight: 32
    lineHeightMode: Text.FixedHeight
    font.pixelSize: 32
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
}
