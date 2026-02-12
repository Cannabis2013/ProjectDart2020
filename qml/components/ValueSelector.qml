import QtQuick 2.15
import QtQuick.Controls 2.12

Rectangle {
  signal requestTournamentPage

  property string label: "Label"
  property var model: []
  property int currentIndex: 0
  onCurrentIndexChanged: selectorValue.currentIndex = currentIndex
  property string currentValue: ""
  onCurrentValueChanged: currentIndex = model.indexOf(currentValue)
  readonly property string current: selectorValue.currentText

  color: "transparent"
  height: 48

  Text {
    id: selectorLabel

    width: 192
    height: parent.height

    text: parent.label

    color: "lightgray"
    font.pixelSize: 20

    verticalAlignment: Text.AlignVCenter
  }

  ComboBox {
    id: selectorValue
    height: parent.height
    anchors.left: selectorLabel.right
    anchors.right: parent.right
    anchors.topMargin: 4
    model: parent.model
    font.pixelSize: 20
    currentIndex: 0
    padding: 8
  }
}
