import QtQuick 6.0
import QtQuick.Controls 6.0
import "../utils/nameUtils.js" as Names

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

      Rectangle {
        color: "black"

        property string playerName: playersInfo.players[index]
        onPlayerNameChanged: {
          playerNameText.text = Names.shortenName(playerName, 9)

          playerRemaining.text = dartsScores.remaining(playerName)

          const indexes = JSON.parse(dartsTurns.indexes())
          const currentRoundIndex = indexes.roundIndex
          let inputs = []

          let inputsAsString = ""
          for (let roundIndex = 1; roundIndex <= currentRoundIndex; roundIndex++) {
            inputs = JSON.parse(dartsInputs.inputs(playerName,roundIndex))
            if(inputs.length <= 0) continue

            inputsAsString = inputs.reduce((s,input) => s + `${input.mod}${input.point} `,"")

            inputsModel.append({"value": `Round ${roundIndex}: ${inputsAsString}`})
          }
        }

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

          anchors.horizontalCenter: parent.horizontalCenter
          anchors.top: playerRemaining.bottom
          anchors.topMargin: 8
          anchors.bottom: parent.bottom

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
    playersInfo.players = dartsPlayers.all()
    inputsListRepeater.model = playersInfo.players.length

    const current = dartsPlayers.current()
    const playerIndex = dartsPlayers.playerIndex(current)
    playersSwipeView.setCurrentIndex(
          (inputsListRepeater.count - 1) - playerIndex)
  }
}
