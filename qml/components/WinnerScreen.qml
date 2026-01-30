import QtQuick 6.0
import QtQuick.Controls 6.0

Rectangle {
  id: winnerModal

  color: "black"

  signal menuRequest
  signal restartClicked
  signal undoClicked
  signal close

  QtObject {
    id: playersInfo
    property var players: []
    property var statistics: []
    property var scores: []

    function getStats(index) {
      const stats = statistics[index]
      return `
Player: ${players[index]}
Remaining: ${scores[index]}
Low: ${stats.low}
Avarage: ${stats.average}
High: ${stats.high}`
    }
  }

  Image {
    id: trophyImage
    source: "qrc:/Ressources/trophy.png"
    width: 128
    height: 128
    y: 64
    anchors.horizontalCenter: parent.horizontalCenter
  }

  Text {
    id: winnerText
    anchors.top: trophyImage.bottom
    anchors.topMargin: 6
    text: ""
    width: parent.width
    height: 32
    horizontalAlignment: Text.AlignHCenter
    font.pointSize: 20
    font.weight: 700
    color: "white"
  }

  SwipeView {
    id: playerInfo
    width: parent.width

    anchors.top: winnerText.bottom
    anchors.topMargin: 12
    anchors.bottom: menuButton.top
    anchors.horizontalCenter: parent.horizontalCenter

    padding: 8

    Repeater {
      id: repeater

      Text {
        height: playerInfo.height
        width: playerInfo.width
        text: playersInfo.getStats(index)
        font.pointSize: 16
        color: "white"
      }
    }
  }

  Button {
    id: menuButton
    anchors.bottomMargin: 64
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    width: 128
    height: 48
    flat: true
    font.pointSize: 24
    text: "Menu"
    onClicked: {
      winnerModal.menuRequest()
      winnerModal.close()
    }
  }

  Button {
    id: undoButton
    anchors.bottomMargin: 64
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter
    width: 128
    height: 48
    flat: true
    font.pointSize: 24
    text: "Undo"
    onClicked: {
      winnerModal.undoClicked()
      winnerModal.close()
    }
  }

  Button {
    id: restartButton
    anchors.bottomMargin: 64
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    width: 144
    height: 48
    flat: true
    font.pointSize: 24
    text: "Restart"
    onClicked: {
      winnerModal.restartClicked()
      winnerModal.close()
    }
  }

  Component.onCompleted: {
    const info = JSON.parse(winnerInfo.info())
    winnerText.text = info.name

    playersInfo.players = dartsPlayers.all()
    repeater.model = playersInfo.players.length

    playersInfo.statistics = JSON.parse(dartsStats.all())
    playersInfo.scores = dartsScores.all()
  }
}
