import QtQuick 2.1
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3

Item {
  id: messageItem

  height: 48

  function update(finishRow) {
    textContent.text = finishRow
    messageItem.visible = finishRow.length > 0
  }

  Image {
    id: messageIcon

    anchors.verticalCenter: parent.verticalCenter

    source: "qrc:/pictures/Ressources/Pictures/dartsplate.png"

    height: 18
    width: 25
  }

  Text {
    id: textContent

    anchors.left: messageIcon.right
    anchors.leftMargin: 6

    height: parent.height

    font.pixelSize: 20
    font.weight: Font.Bold
    color: "white"

    text: messageItem.message

    verticalAlignment: Text.AlignVCenter
  }
}
