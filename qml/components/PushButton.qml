import QtQuick 6.0

Item {
  id: pushButton

  signal clicked

  property int labelSize: 16
  onLabelSizeChanged: buttonText.font.pixelSize = labelSize
  property string label: ""
  onLabelChanged: buttonText.text = label

  height: 40
  width: 64
  onEnabledChanged: opacity = enabled ? 1 : .5

  QtObject{
    id: buttonVars
    property color bg: "#2f2f2f"
    property color pressedBg: "#4f4f4f"
  }
  Rectangle {
    id: background
    anchors.fill: parent
    color: buttonVars.bg
    Behavior on color {
      ColorAnimation {
        duration: 125
      }
    }
  }
  Text {
    id: buttonText
    anchors.fill: parent
    color: "lightgray"
    font.pixelSize: pushButton.labelSize
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    text: pushButton.label
  }
  MouseArea {
    id: buttonMouseArea
    anchors.fill: parent
    cursorShape: "PointingHandCursor"
    onPressed: background.color = buttonVars.pressedBg
    onClicked: pushButton.clicked()
    onReleased: background.color = buttonVars.bg
  }
}
