import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "../../../utils/nameUtils.js" as Names

Rectangle {
  clip: true

  color: "black"

  signal close

  QtObject{
    id: playersInfo

    property var players: []
  }

  SwipeView{
    id: playersSwipeView

    clip: true

    width: parent.width

    anchors.top: parent.top
    anchors.margins: 8
    anchors.bottom: dialogButton.top

    padding: 8

    Repeater{
      id: inputsListRepeater

      PlayersInfoView{
        width: playersSwipeView.width
        height: playersSwipeView.height

        playerName: playersInfo.players[index].name
      }
    }
  }

  Button{
    id: dialogButton

    text: "Close"
    width: 128
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 8

    onClicked: close()
  }

  Component.onCompleted: {
    playersInfo.players = JSON.parse(dartsPlayers.all())
    inputsListRepeater.model = playersInfo.players.length

    const current = JSON.parse(dartsPlayers.current())
    const index = dartsPlayers.playerIndex(current.name)
    playersSwipeView.currentIndex = index
  }
}
