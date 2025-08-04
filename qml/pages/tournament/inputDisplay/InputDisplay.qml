import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import "inputDisplay.js" as Scripts

Item {
  function add(modId, point) {
    Scripts.addInput(modId, point)
  }

  function inputs() {
    return inputMem.inputs
  }

  function reset() {
    Scripts.reset()
  }

  QtObject {
    id: inputMem
    property var inputs: []
    property int initialScore: 0
  }

  TextBox {
    id: inputsBox
    label: "INPUTS"
    anchors.margins: 6
    anchors.top: parent.top
    anchors.left: parent.left
    width: 128
    height: 24
  }

  TextBox {
    id: scoreBox
    label: "SCORE"
    anchors.margins: 6
    anchors.top: parent.top
    anchors.left: inputsBox.right
    width: 80
    height: 24
  }

  TextBox {
    id: scorePreview
    label: "PREVIEW"
    anchors.margins: 6
    anchors.top: parent.top
    anchors.left: scoreBox.right
    width: 96
    height: 24
  }

  Button {
    id: clearButton
    text: "Flush"
    width: 80
    height: 32
    font.pixelSize: 12
    anchors.margins: 6
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    onClicked: Scripts.reset()
  }

  Button {
    id: removeButton
    text: "Pop"
    width: 70
    height: 32
    font.pixelSize: 12
    anchors.margins: 6
    anchors.left: clearButton.right
    anchors.bottom: parent.bottom
    onClicked: Scripts.pop()
  }
}
