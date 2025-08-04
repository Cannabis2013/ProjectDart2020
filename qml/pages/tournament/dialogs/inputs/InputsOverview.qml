import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "inputsScripts.js" as Scripts

Dialog {
  width: parent.width * 0.95
  height: parent.height * 0.95
  anchors.centerIn: parent

  ColumnLayout {
    width: parent.width
    height: parent.height
    spacing: 48

    Text {
      id: playerName
      color: "white"
      font.pointSize: 32
      width: parent.width
    }

    ListView {
      id: inputsList
      clip: true

      Layout.fillHeight: true
      Layout.preferredWidth: 192
      Layout.alignment: Qt.AlignCenter

      boundsBehavior: ListView.StopAtBounds
      spacing: 6

      model: ListModel {
        id: inputsModel
      }

      delegate: InputDelegate {
        id: inputDelegate
        height: 32
        width: ListView.view.width
      }

      Component.onCompleted: currentIndex = count - 1
    }
  }

  standardButtons: Dialog.Ok

  Component.onCompleted: Scripts.init()
}
