import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3

Item {
  signal clearClicked
  signal popClicled

  function update(inputs = []) {
    let text = ""
    inputs.forEach(input => text += `${input.modId}${input.point} `)
    textInputs.text = text
  }

  Rectangle {
    color: "#4f4f4f"
    radius: 6
    anchors.left: parent.left
    width: 170
    height: parent.height

    Text {
      id: textLabel
      anchors.left: parent.left
      anchors.leftMargin: 6
      height: parent.height
      width: 36
      text: "INPUTS"
      font.pixelSize: 12
      color: "lightgray"
      verticalAlignment: Text.AlignVCenter
    }

    Text {
      id: textInputs
      anchors.left: textLabel.right
      anchors.leftMargin: 12
      anchors.right: parent.right
      height: parent.height
      font.pixelSize: 18
      font.weight: Font.Bold
      color: "white"
      verticalAlignment: Text.AlignVCenter
    }
  }

  Button {
    id: clearButton
    text: "Flush"
    width: 80
    height: 30
    font.pixelSize: 12
    anchors.right: parent.right
    onClicked: clearClicked()
  }

  Button {
    id: removeButton
    width: 70
    height: 30
    font.pixelSize: 12
    anchors.right: clearButton.left
    text: "Pop"
    onClicked: popClicled()
  }
}
