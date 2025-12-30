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
    buttonText.text = label
  }

  Behavior on scale{
    NumberAnimation{
      duration: 75
    }
  }

  QtObject{
    id: styles
    property color backgroundColor: "#2f2f2f"
    property color backgroundColorAlt: "#6f6f6f"
    property color labelColor: "white"
    property var cursorShape: "PointingHandCursor"
  }

  FontMetrics{
    id: fontMetrics
    font.pixelSize: pushButton.labelSize
    font.family: buttonText.font.family
  }

  Rectangle{
    id: background
    anchors.fill: parent
    color: styles.backgroundColor
    radius: 6

    Behavior on color {
      ColorAnimation{
        duration: 250
      }
    }
  }

  Text{
    id: buttonText
    anchors.fill: parent
    color: styles.labelColor
    font.pixelSize: pushButton.labelSize
    text: pushButton.label
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }

  MouseArea{
    id: buttonMouseArea
    anchors.fill: parent
    cursorShape: styles.cursorShape
    hoverEnabled: true

    onPressed: pushButton.scale = .9
    onClicked: pushButton.clicked()
    onReleased: pushButton.scale = 1
  }
}
