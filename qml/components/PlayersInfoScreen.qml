import QtQuick 6.0
import QtQuick.Controls 6.0
import "../scripts/playersInfoScreen.js" as Script

Rectangle {
  id: playersInfoScreen

  signal close

  clip: true
  color: "black"

  QtObject {
    id: playersInfo
    property var players: []
  }
  SwipeView {
    id: playersSwipeView
    anchors{left: parent.left;right: parent.right;top: parent.top;bottom: pageIndicator.top}
    Repeater {
      id: inputsListRepeater
      Rectangle {
        color: "black"
        property string playerName: playersInfo.players[index]
        onPlayerNameChanged: Script.updateName(playerName,playerNameText,playerRemaining)
        Text {
          id: playerNameText
          color: "white"
          font.pointSize: 32
          width: parent.width
          height: 64
          horizontalAlignment: Text.AlignHCenter
        }
        Text {
          id: playerRemaining
          anchors.top: playerNameText.bottom
          color: "white"
          text: ""
          font.pointSize: 24
          width: parent.width
          height: 64
          horizontalAlignment: Text.AlignHCenter
        }
        ListView {
          id: inputsList
          width: 192
          anchors {
            top: playerRemaining.bottom;
            bottom:parent.bottom;
            horizontalCenter: parent.horizontalCenter;
            topMargin: 8;
          }
          boundsBehavior: ListView.StopAtBounds
          spacing: 6
          model: ListModel {
            id: inputsModel
          }
          delegate: Text {
            id: inputDelegate
            height: 32
            width: ListView.view.width
            color: "white"
            text: value
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
          }
          Component.onCompleted: currentIndex = count - 1
        }
      }
    }
  }

  PageIndicator {
    id: pageIndicator
    interactive: false
    currentIndex: playersSwipeView.currentIndex
    anchors{
      horizontalCenter: parent.horizontalCenter;
      bottom: dialogButton.top;
      bottomMargin: 8;
    }
    count: playersSwipeView.count
    height: 12
  }

  Button {
    id: dialogButton
    text: "Close"
    width: 128
    anchors{
      horizontalCenter: parent.horizontalCenter;
      bottom: parent.bottom;
      bottomMargin: 8
    }
    onClicked: playersInfoScreen.close()
  }
  Component.onCompleted: Script.init()
}
