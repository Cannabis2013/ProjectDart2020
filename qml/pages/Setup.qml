import QtQuick 2.15
import QtQuick.Controls 2.12
import "../templates"
import "../components/controls"

PageWithHeader {
  signal requestTournamentPage

  padding: 9

  pageTitle: "Setup game"

  function isPortrait() {
    return width > height || width >= 800
  }

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

    anchors.top: parent.top
    anchors.topMargin: 9

    width: !isPortrait() ? parent.width : 256

    label: qsTr("Initial remaining:")

    model: [101, 201, 301, 501]

    currentIndex: 2
  }

  ValueSelector {
    id: openingSelector

    anchors.top: initialScoreSelector.bottom
    anchors.topMargin: 9

    width: !isPortrait() ? parent.width : 256

    label: qsTr("Opens with:")

    model: ["None", "number", "double"]
  }

  ValueSelector {
    id: closeningSelector

    anchors.top: openingSelector.bottom
    anchors.topMargin: 9

    width: !isPortrait() ? parent.width : 256

    label: qsTr("Close with:")

    model: ["None", "number", "double"]
  }

  Label {
    id: playerLabel
    anchors.top: isPortrait() ? parent.top : closeningSelector.bottom
    anchors.right: parent.right
    anchors.margins: 8

    font.pixelSize: 24

    height: 32
    width: isPortrait() ? parent.width / 2 : parent.width

    horizontalAlignment: Label.AlignHCenter

    text: "Choose players"
  }

  Item {
    id: playerSelectorWrapper

    anchors.top: playerLabel.bottom
    anchors.bottom: goButton.top
    anchors.right: parent.right
    anchors.margins: 9

    width: isPortrait() ? parent.width / 2 : parent.width
  }

  ListView {
    id: playerSelector

    anchors.horizontalCenter: playerSelectorWrapper.horizontalCenter
    anchors.top: playerSelectorWrapper.top
    anchors.bottom: playerSelectorWrapper.bottom

    width: parent.width

    clip: true

    boundsBehavior: ListView.StopAtBounds

    property var selectedNames: []

    spacing: 6

    model: ListModel {
      id: playerListModel
    }

    delegate: Text {
      property bool selected: false

      height: 32
      width: ListView.view.width

      color: "gray"
      font.pixelSize: 20

      text: name
      horizontalAlignment: Text.AlignHCenter

      MouseArea {
        anchors.fill: parent
        onClicked: {
          const selected = playerSelector.selectedNames
          if (selected.includes(name)) {
            playerSelector.selectedNames = selected.filter(n => n !== name)
            parent.color = "gray"
          } else {
            selected.push(name)
            parent.color = "white"
          }
        }
      }

      Component.onCompleted: {
        color = playerSelector.selectedNames.includes(name) ? "white" : "gray"
      }
    }
  }

  Button {
    id: goButton

    anchors.bottom: parent.bottom
    anchors.bottomMargin: 8
    anchors.horizontalCenter: parent.horizontalCenter

    font.pixelSize: 32

    text: qsTr("Start game")

    onClicked: {
      if (init())
        requestTournamentPage()
    }
  }

  Component.onCompleted: {
    JSON.parse(dartsPlayers.available())
      .map(player => {
             return {
               "name": player.name
             }
           })
      .forEach(
         nameObj => playerListModel.append(nameObj))
  }
}
