import QtQuick 2.15
import QtQuick.Controls 2.12

Rectangle {
  color: "transparent"

  height: 80

  signal requestTournamentPage

  property string label: "Label"
  property var model: []

  property int currentIndex: 0

  readonly property string current: controlValue.currentText

  Text {
    id: controlLabel

    width: parent.width
    height: 32

    anchors.horizontalCenter: parent.horizontalCenter

    text: parent.label

    color: "white"
    font.pixelSize: 20

    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
  }

  ComboBox {
    id: controlValue

    anchors.top: controlLabel.bottom
    anchors.topMargin: 4
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom

    width: parent.width

    model: parent.model
    font.pixelSize: 20

    currentIndex: parent.currentIndex
  }
}
