import QtQuick 2.1

Item {
  id: messageItem

  function update(finishRow) {
    textContent.text = finishRow
  }

  Text {
    id: textContent

    anchors.fill: parent

    font.pixelSize: 48
    font.weight: Font.Bold
    color: "white"

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
}
