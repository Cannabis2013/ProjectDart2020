import QtQuick 6.0
import QtQuick.Controls 6.0

Rectangle {
  id: playersInfoScreen

  clip: true

  color: "black"

  signal close

  QtObject {
    id: playersInfo

    property var players: []
  }

  SwipeView {
    id: playersSwipeView

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: pageIndicator.top

    Repeater {
      id: inputsListRepeater

      PlayersInfoView {
        width: SwipeView.view.width
        height: SwipeView.view.height

        playerName: playersInfo.players[index].name
      }
    }
  }

  PageIndicator {
    id: pageIndicator

    interactive: false

    currentIndex: playersSwipeView.currentIndex

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: dialogButton.top
    anchors.bottomMargin: 8

    count: playersSwipeView.count

    height: 48
  }

  Button {
    id: dialogButton

    text: "Close"
    width: 128
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 8

    onClicked: playersInfoScreen.close()
  }

  Component.onCompleted: {
    playersInfo.players = JSON.parse(dartsPlayers.all())
    inputsListRepeater.model = playersInfo.players.length

    const current = JSON.parse(dartsPlayers.current())
    const playerIndex = dartsPlayers.playerIndex(current.name)
    playersSwipeView.setCurrentIndex(
          (inputsListRepeater.count - 1) - playerIndex)
  }
}
