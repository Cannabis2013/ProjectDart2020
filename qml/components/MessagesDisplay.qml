import QtQuick 2.1

Item {
  id: messageItem

  function update(finishRow) {
    textContent.text = finishRow
    messageItem.visible = finishRow.length > 0
  }

  Image {
    id: messageIcon

    anchors.verticalCenter: parent.verticalCenter

    source: "qrc:/pictures/Ressources/Pictures/dartsplate.png"

    height: 32
    width: 32
  }

  Text {
    id: textContent

    anchors.left: messageIcon.right
    anchors.leftMargin: 6

    height: parent.height

    font.pixelSize: 32
    font.weight: Font.Bold
    color: "white"

    verticalAlignment: Text.AlignVCenter
  }
}
