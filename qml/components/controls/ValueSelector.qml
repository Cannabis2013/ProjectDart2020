import QtQuick 2.15
import QtQuick.Controls 2.12

Rectangle {
  color: "transparent"

  width: 256
  height: 32

  signal requestTournamentPage

  property string label: "Label"
  property var model: []

  property int currentIndex: 0

  readonly property string current: selector.currentText

  Text {
    id: label
    anchors.left: parent.left
    text: parent.label
    width: 128
    height: parent.height
    color: "white"
    verticalAlignment: Text.AlignVCenter
  }

  ComboBox {
    id: selector
    anchors.right: parent.right
    model: parent.model
    height: parent.height
    width: 128
    currentIndex: parent.currentIndex
  }
}
