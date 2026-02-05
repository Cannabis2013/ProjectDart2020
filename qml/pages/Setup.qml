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
  background: Rectangle{
    anchors.fill: parent
    color: "#1f1f1f"
  }

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
        currentIndex: 3
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
        delegate: PlayerDelegate {
          id: playerItem
          onClicked: Script.selectPlayer(playerItem.index)
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
  Component.onCompleted: Script.init()
}
