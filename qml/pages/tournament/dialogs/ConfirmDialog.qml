import QtQuick 6.0
import QtQuick.Controls 6.0

Dialog {
  id: dialogRect

  width: 256
  height: 288

  anchors.centerIn: parent

  property string text: "Sure?"
  onTextChanged: modalText.text = text

  contentItem: Rectangle {
    color: "transparent"
    Text {
      id: modalText
      anchors.fill: parent
      wrapMode: Text.WordWrap
      color: "white"
      font.pointSize: 16
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      text: qsTr(dialogRect.text)
    }
  }

  standardButtons: Dialog.Ok | Dialog.Cancel
}
