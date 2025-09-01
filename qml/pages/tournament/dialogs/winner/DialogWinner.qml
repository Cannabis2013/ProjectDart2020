import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3

Rectangle {
  id: winnerModal

  anchors.fill: parent
  color: "black"

  signal restartClicked
  signal undoClicked

  QtObject {
    id: playersInfo
    property var players: []
    property var statistics: []

    function getPlayer(index) {
      return players[index]
    }

    function getStats(index) {
      const stats = statistics[index]
      return `Low: ${stats.low}\nAvarage: ${stats.average}\nHigh: ${stats.high}`
    }
  }

  Button {
    id: menuButton
    anchors.left: parent.left
    width: 128
    height: 48
    flat: true
    font.pointSize: 24
    text: "Menu"
    onClicked: {
      winnerModal.visible = false
      menuRequest()
    }
  }

  Button {
    id: undoButton
    anchors.horizontalCenter: parent.horizontalCenter
    width: 128
    height: 48
    flat: true
    font.pointSize: 24
    text: "Undo"
    onClicked: {
      winnerModal.visible = false
      undoClicked()
    }
  }

  Button {
    id: restartButton
    anchors.right: parent.right
    width: 144
    height: 48
    flat: true
    font.pointSize: 24
    text: "Restart"
    onClicked: {
      winnerModal.visible = false
      restartClicked()
    }
  }

  Text {
    id: winnerText
    text: ""
    y: 128
    width: parent.width
    height: 32
    horizontalAlignment: Text.AlignHCenter
    font.pointSize: 16
    font.weight: 700
    color: "white"
  }

  SwipeView {
    id: playerInfo
    width: parent.width - 16
    anchors.top: winnerText.bottom
    anchors.topMargin: 12
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter

    Repeater {
      id: repeater

      Rectangle {
        color: "transparent"
        height: playerInfo.height
        width: playerInfo.width
        Text {
          id: pageText
          width: parent.width
          height: 32
          text: playersInfo.getPlayer(index).name
          horizontalAlignment: Text.AlignHCenter
          font.pointSize: 12
          color: "white"
        }

        Text {
          anchors.bottom: parent.bottom
          width: parent.width
          height: parent.height - 48
          text: playersInfo.getStats(index)
          font.pointSize: 12
          color: "white"
        }
      }
    }
  }

  Component.onCompleted: {
    const info = JSON.parse(dartsPlayers.winnerInfo())
    winnerText.text = info.winnerName

    playersInfo.players = JSON.parse(dartsPlayers.all())
    repeater.model = playersInfo.players.length

    playersInfo.statistics = JSON.parse(dartsStats.all())
  }
}
