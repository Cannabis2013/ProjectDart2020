import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3

Item {
  signal pop
  signal flush

  width: 128
  height: 32

  PushButton {
    id: flushButton
    label: "Flush"
    anchors.right: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.rightMargin: 4
    height: parent.height
    onClicked: flush()
  }

  PushButton{
    id: popButton
    label: "Pop"
    anchors.left: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.leftMargin: 4
    height: parent.height
    onClicked: pop()
  }
}
