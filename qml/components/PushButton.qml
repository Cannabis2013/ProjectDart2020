import QtQuick 6.0

Item {
  id: pushButton

  signal clicked

  height: 40
  width: 64

  property int labelSize: 16
  onLabelSizeChanged: buttonText.font.pixelSize = labelSize

  property string label: ""
  onLabelChanged: {
    buttonText.text = label
  }

  Behavior on scale{
    NumberAnimation{
      duration: 75
    }
  }

  FontMetrics{
    id: fontMetrics
    font.pixelSize: labelSize
    font.family: buttonText.font.family
  }

  Rectangle{
    id: background
    anchors.fill: parent
    color: "#3f3f3f"
    radius: 12

    Behavior on color {
      ColorAnimation{
        duration: 250
      }
    }
  }

  Text{
    id: buttonText
    anchors.fill: parent
    color: "white"
    font.pixelSize: pushButton.labelSize
    text: pushButton.label
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  MouseArea{
    id: buttonMouseArea
    anchors.fill: parent
    cursorShape: "PointingHandCursor"
    hoverEnabled: true

    onPressed: pushButton.scale = .9
    onClicked: pushButton.clicked()
    onReleased: pushButton.scale = 1
    onHoveredChanged: background.color = containsMouse ?
                        "#6f6f6f" : "#3f3f3f"
  }
}
