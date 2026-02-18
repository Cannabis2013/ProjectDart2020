import QtQuick 6.0
import "../scripts/nameUtils.js" as Names
import "../scripts/infoDisplay.js" as Script

Item {
  id: playerInfo
  signal openPlayerInfoDialog

  function update(inputs) {
    let remaining = dartsScores.current()
    remaining -= calculateSum(inputs)
    const player = dartsPlayers.current()
    playerName.text = Names.shortenName(player, 9)
    playerRemaining.text = remaining >= 0 ? remaining : 0
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

  Text {
    id: playerName
    clip: true
    height: 48
    anchors {
      top: parent.top
      left: parent.left
      right: parent.right
      margins: 8
    }
    font.pixelSize: 40
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    MouseArea {
      anchors.fill: parent
      onClicked: playerInfo.openPlayerInfoDialog()
    }
  }
  Text {
    id: playerRemaining
    anchors {
      top: playerName.bottom
      bottom: parent.bottom
      margins: 8
    }
    width: parent.width
    font.pixelSize: 0.5*(height >= 0 ? height : 0) + 24
    font.weight: Font.Bold
    color: "lightgray"
    verticalAlignment: Qt.AlignVCenter
    horizontalAlignment: Qt.AlignHCenter
  }
}
