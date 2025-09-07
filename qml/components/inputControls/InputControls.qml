import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3

Item {
  signal pop
  signal flush

  Button {
    id: flushButton
    text: "Flush"
    width: 128
    height: 40
    font.pixelSize: 20
    anchors.right: popButton.left
    anchors.bottom: parent.bottom
    anchors.margins: 6
    onClicked: flush()
  }

  Button {
    id: popButton
    text: "Pop"
    width: 96
    height: 40
    font.pixelSize: 20
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.margins: 6
    onClicked: pop()
  }
}
