import QtQuick 6.0
import QtQuick.Controls
import QtQuick.Layouts 1.3

Item {
  signal pop
  signal flush

  Button {
    id: flushButton
    text: "Flush"
    width: 96
    height: 40
    font.pixelSize: 14
    anchors.right: popButton.left
    anchors.bottom: parent.bottom
    anchors.margins: 6
    onClicked: flush()
  }

  Button {
    id: popButton
    text: "Pop"
    width: 80
    height: 40
    font.pixelSize: 14
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.margins: 6
    onClicked: pop()
  }
}
