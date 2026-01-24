import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts
import "../components"

Page {
  id: setupPage

  signal requestTournamentPage
  signal backClicked

  function isLandscape() {
    return width > height || width >= 800;
  }

  function initializeController() {
    let item = null;
    let selectedNames = [];
    for(let i = 0; i < playerListModel.count;i++){
      item = playerListModel.get(i);
      if(item.selected)
        selectedNames.push(item.name);
    }

    if (selectedNames.length <= 0)
      return false;

    const selectedOpenMod = openingSelector.current;
    let openMod = '';
    if (selectedOpenMod === "Number")
      openMod = 'S';
    else if (selectedOpenMod === "Double")
      openMod = 'D';
    else if (selectedOpenMod === "Tripple")
      openMod = 'T';

    const closeningMod = closeningSelector.current;

    let closeMod = '';
    if (closeningMod == "Number")
      closeMod = 'S';
    else if (closeningMod == "Double")
      closeMod = 'D';

    const values = {
      "players": selectedNames,
      "initialScore": parseInt(initialScoreSelector.current),
      "openingMod": openMod,
      "closeningMod": closeMod
    };
    dartsInitializer.init(JSON.stringify(values));
    return true;
  }

  header: PageHeader {
    pageTitle: "Setup game"
    onBack: setupPage.backClicked()
  }

  QtObject{
    id: selectedInfo
    property int count: 0
    onCountChanged: goButton.enabled = count > 0
  }

  padding: 9

  GridLayout {
    width: parent.width
    anchors.top: parent.top
    anchors.bottom: goButton.top
    columns: setupPage.isLandscape() ? 2 : 1
    rows: setupPage.isLandscape() ? 1 : 2
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
        model: ["None", "Number", "Double"]
      }
    }

    Item {
      id: playerContainer
      Layout.alignment: Qt.AlignHCenter
      Layout.fillHeight: true
      Layout.preferredWidth: 384
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
          height: 64
          width: ListView.view.width
          Text {
            id: delegateText
            anchors.fill: parent
            anchors.margins: 9
            color: "lightgray"
            font.pixelSize: 28
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: playerDelegate.name
          }
          MouseArea {
            anchors.fill: parent
            onClicked: function() {
              const model = playerListModel.get(playerDelegate.index)
              const currentCount = selectedInfo.count
              selectedInfo.count = model.selected ? currentCount - 1 :
                                                    currentCount + 1
              model.selected = !model.selected
            }
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
    width: setupPage.isLandscape() ? 192 : parent.width
    height: 64
    backgroundColor: "green"
    labelSize: 28
    label: qsTr("Start game")
    enabled: false
    onClicked: {
      if (setupPage.initializeController())
        setupPage.requestTournamentPage();
    }
  }
  Component.onCompleted: {
    const playerNames = ["Max van Gerwen","Jes Humphreys","Simone Clayton",
      "Rasmus Smith","Hjalte Van Veen","Bjarke Anderson",
      "Ewelina Ratajski","Laila Aspinal","Lars Wright",
      "Benjamin Reus","Storm Gates"];

    playerNames.forEach(playerName => {
      playerListModel.append({"name": playerName,"selected": false})
    })
  }
}
