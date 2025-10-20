import QtQuick 6.0

Item {
  id: pushButton

  signal clicked

  height: -1
  width: -1

  property int labelSize: 16
  onLabelSizeChanged: {
    buttonText.font.pixelSize = labelSize
    updateButtonGeometry()
  }

  function updateButtonGeometry(){
    if(width !== -1 || height !== -1) return
    fontMetrics.font.pixelSize = labelSize
    const rect = fontMetrics.boundingRect(label)
    pushButton.width = rect.width + 32
    pushButton.height = fontMetrics.height + 16
  }

  property string label: ""
  onLabelChanged: {
    updateButtonGeometry()
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
