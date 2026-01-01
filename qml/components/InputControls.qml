import QtQuick 6.0

Item {
  signal pop
  signal flush

  width: 160
  height: 32

  PushButton {
    id: flushButton

    label: "Flush"

    height: parent.height
    width: 80

    anchors.right: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.rightMargin: 4

    onClicked: parent.flush()

    labelSize: 24
  }

  PushButton{
    id: popButton

    label: "Pop"

    anchors.left: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.leftMargin: 4

    height: parent.height
    width: 80

    onClicked: parent.pop()

    labelSize: 24
  }
}
