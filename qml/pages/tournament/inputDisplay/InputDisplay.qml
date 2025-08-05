import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "inputDisplay.js" as Scripts

Item {
  signal pop
  signal flush

  function update(inputs, inputsScore) {
    Scripts.updateDisplays(inputs, inputsScore)
  }

  QtObject {
    id: inputMem
    property var inputs: []
    property int initialScore: 0
  }

  TextBox {
    id: scoreBox
    label: "SCORE"
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.bottom: parent.verticalCenter
    anchors.margins: 6
    width: 96
    fontSize: 14
  }

  TextBox {
    id: inputsBox
    label: "INPUTS"
    anchors.top: parent.top
    anchors.left: scoreBox.right
    anchors.bottom: parent.verticalCenter
    anchors.margins: 6
    width: 128
    fontSize: 14
  }

  Button {
    id: flushButton
    text: "Flush"
    width: 96
    height: 40
    font.pixelSize: 14
    anchors.right: popButton.left
    anchors.bottom: parent.bottom
    anchors.margins: 6
    onClicked: flush()
  }

  Button {
    id: popButton
    text: "Pop"
    width: 80
    height: 40
    font.pixelSize: 14
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.margins: 6
    onClicked: pop()
  }
}
