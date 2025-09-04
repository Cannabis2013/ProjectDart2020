import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "../../../utils/nameUtils.js" as Names

Item{
  property string playerName: ""
  onPlayerNameChanged: {
    playerNameText.text = Names.shortenName(playerName,9)

    playerRemaining.text = dartsScores.remaining(playerName)

    const json = dartsInputs.inputs(playerName)
    const inputs = JSON.parse(json)

    let inputElement = {}
    let input = {}
    for (var i = 0; i < inputs.length; i++) {
      input = inputs[i]
      inputElement = {
        "round": input.roundIndex,
        "value": `${input.mod} ${input.point}`
      }
      inputsModel.append(inputElement)
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

  Text{
    id: playerRemaining

    anchors.top: playerNameText.bottom

    color: "white"
    text: ""
    font.pointSize: 24

    height: 64
    width: parent.width

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

    model: ListModel{
      id: inputsModel
    }

    delegate: Item {
      id: inputDelegate
      clip: true
      height: 32
      width: inputsList.width

      Image {
        id: arrowImage
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        height: 32
        width: 32
        source: "qrc:/pictures/Ressources/Pictures/dartsplate.png"
      }

      Text {
        id: roundText
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: arrowImage.right
        anchors.leftMargin: 6
        width: 20
        text: round
        font.pointSize: 20
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"
      }

      Text {
        clip: true
        text: value
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: roundText.right
        anchors.leftMargin: 6
        anchors.right: parent.right
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font.pointSize: 20
        font.weight: Font.Bold
      }
    }

    Component.onCompleted: currentIndex = count - 1
  }
}
