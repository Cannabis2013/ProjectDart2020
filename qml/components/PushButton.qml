import QtQuick 6.0

Item {
  id: pushButton

  signal clicked

  height: 40
  width: 64

  onEnabledChanged: opacity = enabled ? 1 : .5

  property int labelSize: 16
  onLabelSizeChanged: buttonText.font.pixelSize = labelSize

  property string label: ""
  onLabelChanged: {
    buttonText.text = label;
  }

  property string backgroundColor: "#2f2f2f"
  onBackgroundColorChanged: background.color = backgroundColor

  Behavior on scale {
    NumberAnimation {
      duration: 75
    }
  }

  FontMetrics {
    id: fontMetrics
    font.pixelSize: pushButton.labelSize
    font.family: buttonText.font.family
  }

  Rectangle {
    id: background
    anchors.fill: parent
    color: pushButton.backgroundColor
    radius: 6

    Behavior on color {
      ColorAnimation {
        duration: 250
      }
    }
  }

  Text {
    id: buttonText
    anchors.fill: parent
    color: "lightgray"
    font.pixelSize: pushButton.labelSize
    text: pushButton.label
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  MouseArea {
    id: buttonMouseArea
    anchors.fill: parent
    cursorShape: "PointingHandCursor"
    hoverEnabled: true

    onPressed: pushButton.scale = .9
    onClicked: pushButton.clicked()
    onReleased: pushButton.scale = 1
  }
}
