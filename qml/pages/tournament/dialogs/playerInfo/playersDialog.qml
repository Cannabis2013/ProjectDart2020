import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "../../../../utils/nameUtils.js" as Names

Dialog {
  clip: true

  width: parent.width * 0.95
  height: parent.height * 0.95
  anchors.centerIn: parent

  padding: 0


  QtObject{
    id: playersInfo

    property var players: []
  }

  SwipeView{
    id: playersSwipeView
    clip: true

    anchors.fill: parent

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

  standardButtons: Dialog.Ok

  Component.onCompleted: {
    playersInfo.players = JSON.parse(dartsPlayers.all())
    inputsListRepeater.model = playersInfo.players.length
  }
}
