import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3

Item {
  property string label: ""
  onLabelChanged: textLabel.text = label

  property string value: ""
  onValueChanged: textValue.text = value

  property real fontSize: 12
  onFontSizeChanged: {
    textLabel.font.pixelSize = fontSize
    textValue.font.pixelSize = fontSize
  }

  Text {
    id: textLabel
    anchors.top: parent.top
    anchors.bottom: parent.verticalCenter
    anchors.margins: 3
    width: parent.width
    font.pixelSize: fontSize
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  Text {
    id: textValue
    anchors.top: parent.verticalCenter
    anchors.bottom: parent.bottom
    anchors.margins: 3
    width: parent.width
    font.pixelSize: fontSize
    font.weight: Font.Bold
    color: "white"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
}
