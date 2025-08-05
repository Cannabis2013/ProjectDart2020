import QtQuick 2.1
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "messagesDisplay.js" as Scripts

Item {
  function update() {
    Scripts.updateMessages()
  }

  MessageDisplay {
    id: finishRow
    anchors.left: parent.left
    anchors.verticalCenter: parent.verticalCenter
    height: 32
    width: 192
    imageUrl: "qrc:/pictures/Ressources/Pictures/dartsplate.png"
    imageWidth: 25
    imageHeight: 18
  }

  MessageDisplay {
    id: scoreSpan
    anchors.verticalCenter: parent.verticalCenter
    anchors.right: parent.right
    height: 32
    width: 100
    imageWidth: 18
    imageHeight: 24
  }
}
