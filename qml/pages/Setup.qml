import QtQuick 2.15
import QtQuick.Controls 2.12
import "../components"

Page {
  signal requestTournamentPage

  signal backClicked

  header: PageHeader{
    pageTitle: "Setup game"
    onBack: backClicked()
  }

  padding: 9


  function isLandscape() {
    return width > height || width >= 800
  }

  function initializeController() {
    const selectedNames = playerSelector.selectedNames
    if (selectedNames.length <= 0)
      return false

    const selectedOpenMod = openingSelector.current
    let openMod = 'S'
    if(selectedOpenMod === "Double")
      openMod = 'D'
    else if(selectedOpenMod === "Tripple")
      openMod = ''

    const closeningMod = closeningSelector.current

    let closeMod = ''
    if(closeningMod == "Number")
      closeMod = 'S'
    else if(closeningMod == "Double")
      closeMod = 'D'

    const values = {
      "players": selectedNames,
      "initialScore": parseInt(initialScoreSelector.current),
      "withOpenCondition": openingSelector.current != "None",
      "withCloseCondition": closeMod !== '',
      "closeningMod": closeMod,
      "openingMod": openMod
    }
    dartsInitializer.init(JSON.stringify(values))
    return true
  }

  ValueSelector {
    id: initialScoreSelector
    anchors.top: parent.top
    anchors.topMargin: 9
    width: !isLandscape() ? parent.width : 256
    label: qsTr("Initial remaining:")
    model: [101, 201, 301, 501]
    currentIndex: 2
  }

  ValueSelector {
    id: openingSelector
    anchors.top: initialScoreSelector.bottom
    anchors.topMargin: 9
    width: !isLandscape() ? parent.width : 256
    label: qsTr("Opens with:")
    model: ["None", "Number", "Double"]
  }

  ValueSelector {
    id: closeningSelector
    anchors.top: openingSelector.bottom
    anchors.topMargin: 9
    width: !isLandscape() ? parent.width : 256
    label: qsTr("Close with:")
    model: ["None", "Number", "Double"]
  }

  Label {
    id: playerLabel
    anchors.top: isLandscape() ? parent.top : closeningSelector.bottom
    anchors.right: parent.right
    anchors.margins: 8
    font.pixelSize: 24
    height: 32
    width: isLandscape() ? parent.width / 2 : parent.width
    horizontalAlignment: Label.AlignHCenter
    text: "Choose players"
  }

  ListView {
    id: playerSelector

    property var selectedNames: []

    clip: true

    anchors.top: playerLabel.bottom
    anchors.bottom: goButton.top
    anchors.right: parent.right
    anchors.margins: 9
    anchors.left: isLandscape() ? parent.horizontalCenter : parent.left


    boundsBehavior: ListView.StopAtBounds
    spacing: 9

    model: ListModel {
      id: playerListModel
    }

    delegate: Rectangle {
      color: playerSelector.selectedNames.includes(delegateText.text) ? Qt.rgba(47,47,47,.3) : Qt.rgba(47,47,47,.1)

      radius: 9

      height: 64
      width: ListView.view.width

      Text{
        id: delegateText

        color: "white"
        font.pixelSize: 28

        verticalAlignment: Text.AlignVCenter

        anchors.fill: parent
        anchors.margins: 9

        text: name
      }

      MouseArea {
        anchors.fill: parent

        onClicked: {
          const selected = playerSelector.selectedNames
          if (selected.includes(name)) {
            playerSelector.selectedNames = selected.filter(n => n !== name)
            parent.color = Qt.rgba(47,47,47,.1)
          } else {
            selected.push(name)
            parent.color = Qt.rgba(47,47,47,.3)
          }
        }
      }
    }
  }

  PushButton {
    id: goButton
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 8
    anchors.horizontalCenter: parent.horizontalCenter
    labelSize: 20
    label: qsTr("Start game")
    width: 160
    onClicked: {
      if (initializeController())
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
      .forEach(nameObj => playerListModel.append(nameObj))
  }
}
