import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts
import "../components"
import "../scripts/setupPage.js" as Script

Page {
  id: setupPage

  signal requestTournamentPage
  signal backClicked

  header: PageHeader {
    pageTitle: "Setup game"
    onBack: setupPage.backClicked()
  }
  padding: 9

  QtObject{
    id: selectedInfo
    property int count: 0
    onCountChanged: goButton.enabled = count > 0
  }
  GridLayout {
    width: parent.width
    anchors.top: parent.top
    anchors.bottom: goButton.top
    columns: Script.isLandscape() ? 2 : 1
    rows: Script.isLandscape() ? 1 : 2
    columnSpacing: 9
    rowSpacing: 9
    Item {
      id: controlsContainer
      Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      Layout.preferredWidth: 384
      Layout.preferredHeight: 171
      ValueSelector {
        id: initialScoreSelector
        anchors.top: parent.top
        anchors.topMargin: 9
        width: parent.width
        label: qsTr("Initial remaining:")
        model: [101, 201, 301, 501]
        currentIndex: 2
      }
      ValueSelector {
        id: openingSelector
        anchors.top: initialScoreSelector.bottom
        anchors.topMargin: 9
        width: parent.width
        label: qsTr("Opens with:")
        model: ["None", "Number", "Double", "Tripple"]
      }
      ValueSelector {
        id: closeningSelector
        anchors.top: openingSelector.bottom
        anchors.topMargin: 9
        width: parent.width
        label: qsTr("Close with:")
        currentValue: "Double"
        model: ["None", "Number", "Double"]
      }
    }
    Item {
      id: playerContainer
      Layout.alignment: Qt.AlignHCenter
      Layout.fillHeight: true
      Layout.preferredWidth: 256
      Label {
        id: playerLabel
        anchors.top: parent.top
        anchors.margins: 8
        height: 32
        width: parent.width
        font.pixelSize: 24
        text: "Choose players"
        horizontalAlignment: Label.AlignHCenter
      }
      ListView {
        id: playersListView
        width: parent.width
        anchors {top: playerLabel.bottom; bottom: parent.bottom; margins: 9}
        clip: true
        reuseItems: true
        maximumFlickVelocity: 250000
        boundsBehavior: ListView.StopAtBounds
        spacing: 9
        model: ListModel {
          id: playerListModel
        }
        delegate: Rectangle {
          id: playerDelegate
          required property string name
          required property int index
          required property bool selected
          color: playerDelegate.selected ? Qt.rgba(24, 24, 24, .5) : Qt.rgba(24, 24, 24, .3)
          radius: 9
          height: 40
          width: ListView.view.width
          Text {
            id: delegateText
            anchors.fill: parent
            anchors.margins: 9
            color: "lightgray"
            font.pixelSize: 18
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: playerDelegate.name
          }
          MouseArea {
            anchors.fill: parent
            onClicked: Script.selectPlayer(playerDelegate.index)
          }
        }
      }
    }
  }
  PushButton {
    id: goButton
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 8
    anchors.right: parent.right
    width: Script.isLandscape() ? 192 : parent.width
    height: 64
    backgroundColor: "green"
    labelSize: 28
    label: qsTr("Start game")
    enabled: false
    onClicked: {
      if (Script.initializeController())
        setupPage.requestTournamentPage();
    }
  }
  Component.onCompleted: {
    const playerNames = ["Bulder Max","Jes","Simone Lazare",
      "Rasmus Clemmesen","Hjalte Grønnegård","Bjarke Grønnegård",
      "Ewelina Januszanis","Laila Kjærbo suhr","Lars Skousen",
      "Benjamin Weiss Juhler","Storm","Louise Juhler","Peter C. Block",
      "Eric Molinares","Kent KillerHertz","Per Blindbæk","Kasper Hansen",
      "Muraat Kaan","Thomas Mante","Thomas Gerald","Sune Nørlem",
      "Jesper Ulvedal","Nicolai Hansen","Per Hansen"];

    playerNames.forEach(playerName => {
      playerListModel.append({"name": playerName,"selected": false})
    })
  }
}
