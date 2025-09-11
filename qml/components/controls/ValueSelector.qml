import QtQuick 2.15
import QtQuick.Controls 2.12

Rectangle {
  color: "transparent"

  height: 48

  signal requestTournamentPage

  property string label: "Label"
  property var model: []

  property int currentIndex: 0

  readonly property string current: selectorValue.currentText

  Text {
    id: selectorLabel

    width: 144
    height: parent.height

    text: parent.label

    color: "white"
    font.pixelSize: 14

    verticalAlignment: Text.AlignVCenter
  }

  ComboBox {
    id: selectorValue

    height: parent.height

    anchors.left: selectorLabel.right
    anchors.right: parent.right
    anchors.topMargin: 4

    model: parent.model
    font.pixelSize: 14

    currentIndex: parent.currentIndex
  }
}
