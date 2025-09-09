import QtQuick 2.15
import QtQuick.Controls 2.12
import "../templates"
import "../components/controls"

PageWithHeader {
  signal requestTournamentPage

  padding: 9

  pageTitle: "Setup game"

  function init() {
    const selectedNames = playerSelector.selectedNames
    if (selectedNames.length <= 0)
      return false

    const currentModifier = openingSelector.current

    const modifier = currentModifier === "tripple" ? 'T' : currentModifier === "double" ? 'D' : 'S'

    const values = {
      "players": selectedNames,
      "initialScore": parseInt(initialScoreSelector.current),
      "withOpenCondition": openingSelector.current != "None",
      "withCloseCondition": closeningSelector.current != "None",
      "openingModifier": modifier
    }

    dartsInitializer.init(JSON.stringify(values))
    return true
  }

  ValueSelector {
    id: initialScoreSelector

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.topMargin: 9

    width: parent.width

    label: qsTr("Initial score")

    model: [101, 201, 301, 501]

    currentIndex: 2
  }

  ValueSelector {
    id: openingSelector

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: initialScoreSelector.bottom
    anchors.topMargin: 9

    width: parent.width

    label: qsTr("Opening condition")

    model: ["None", "number", "double"]
  }

  ValueSelector {
    id: closeningSelector

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: openingSelector.bottom
    anchors.topMargin: 9

    width: parent.width

    label: qsTr("Closening condition")

    model: ["None", "number", "double"]
  }

  ListView {
    id: playerSelector

    clip: true

    property var selectedNames: []

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: closeningSelector.bottom
    anchors.bottom: goButton.top
    anchors.margins: 9

    width: parent.width

    model: ListModel {
      id: playerListModel
    }

    delegate: Rectangle {
      property bool selected: false

      color: "transparent"

      height: 32
      width: ListView.view.width

      Text {
        anchors.fill: parent

        color: "white"
        font.pixelSize: 20

        text: name
      }

      MouseArea {
        anchors.fill: parent
        onClicked: {
          const selected = playerSelector.selectedNames
          if (selected.includes(name)) {
            playerSelector.selectedNames = selected.filter(n => n !== name)
            parent.color = "transparent"
          } else {
            selected.push(name)
            parent.color = "gray"
          }
        }
      }

      Component.onCompleted: {
        color = playerSelector.selectedNames.includes(
              name) ? "gray" : "transparent"
      }
    }
  }

  Button {
    id: goButton

    anchors.bottom: parent.bottom
    anchors.bottomMargin: 8
    anchors.horizontalCenter: initialScoreSelector.horizontalCenter

    font.pixelSize: 32

    text: qsTr("Start game")

    onClicked: {
      if (init())
        requestTournamentPage()
    }
  }

  Component.onCompleted: {
    const players = JSON.parse(dartsPlayers.available())
    players.map(player => {
                  return {
                    "name": player.name
                  }
                }).forEach(nameObj => playerListModel.append(nameObj))
  }
}
