import QtQuick 6.0
import QtQuick.Layouts 1.3

Rectangle {
  id: padRect
  clip: true

  property url image: ""
  onImageChanged: padImage.source = image

  Layout.fillHeight: true
  Layout.fillWidth: true

  onPressed: scale = 0.8
  onReleased: scale = 1

  color: "grey"

  signal clicked
  signal pressed
  signal released

  Behavior on scale {
    NumberAnimation {
      duration: 50
    }
  }

  onEnabledChanged: padRect.opacity = enabled ? 1 : 0.2

  property string text: ""
  onTextChanged: buttonText.text = qsTr(text)

  MouseArea {
    anchors.fill: parent
    onClicked: padRect.clicked()
    onPressed: padRect.pressed()
    onReleased: padRect.released()
  }

  Text {
    id: buttonText
    anchors.fill: parent
    font.pointSize: 28
    text: qsTr(padRect.text)
    color: "black"
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
  }

  Image {
    id: padImage
    anchors.centerIn: parent
    source: ""
    width: 42
    height: 31
    rotation: 90
    visible: image != ""
  }
}
