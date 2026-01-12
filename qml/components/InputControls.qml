import QtQuick 6.0

Item {
  id: inputControls

  signal pop
  signal flush
  signal miss

  width: 240 + 18
  height: 32

  PushButton {
    id: flushButton

    label: "Flush"

    height: parent.height
    width: 80

    anchors.right: popButton.left
    anchors.bottom: parent.bottom
    anchors.rightMargin: 4

    onClicked: inputControls.flush()

    labelSize: 24
  }

  PushButton {
    id: popButton

    label: "Pop"

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.leftMargin: 4

    height: parent.height
    width: 80

    onClicked: inputControls.pop()

    labelSize: 24
  }

  PushButton {
    id: bustButton

    label: "Miss"

    anchors.left: popButton.right
    anchors.leftMargin: 4

    width: 80
    height: parent.height

    labelSize: 24

    onClicked: inputControls.miss()
  }
}
