import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3

Rectangle {
  color: "#4f4f4f"

  property string label: ""
  onLabelChanged: textLabel.text = label

  property string value: ""
  onValueChanged: textValue.text = value

  radius: 6
  clip: true

  Text {
    id: textLabel
    anchors.left: parent.left
    anchors.leftMargin: 6
    height: parent.height
    font.pixelSize: 12
    color: "lightgray"
    verticalAlignment: Text.AlignVCenter
  }

  Text {
    id: textValue
    anchors.left: textLabel.right
    anchors.leftMargin: 6
    anchors.right: parent.right
    height: parent.height
    font.pixelSize: 12
    font.weight: Font.Bold
    color: "white"
    verticalAlignment: Text.AlignVCenter
  }
}
