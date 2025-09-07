import QtQuick 2.15
import QtQuick.Controls 2.12

Rectangle {
  color: "transparent"

  width: 256
  height: 96

  signal requestTournamentPage

  property string label: "Label"
  property var model: []

  property int currentIndex: 0

  readonly property string current: controlValue.currentText

  Text {
    id: controlLabel

    width: parent.width
    height: 48

    anchors.horizontalCenter: parent.horizontalCenter

    text: parent.label

    color: "white"
    font.pixelSize: 32

    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
  }

  ComboBox {
    id: controlValue

    anchors.top: controlLabel.bottom
    anchors.topMargin: 4
    anchors.horizontalCenter: parent.horizontalCenter

    height: 48
    width: 144

    model: parent.model
    font.pixelSize: 32

    currentIndex: parent.currentIndex
  }
}
