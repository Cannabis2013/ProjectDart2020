import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts
import "../components"

Page {
  id: setupPage

  signal requestTournamentPage

  signal backClicked

  header: PageHeader {
    pageTitle: "Setup game"
    onBack: setupPage.backClicked()
  }

  padding: 9

  function isLandscape() {
    return width > height || width >= 800;
  }

  function initializeController() {
    const selectedNames = playerSelector.selectedNames;
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
      Layout.preferredHeight: 57 * 3

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

        font.pixelSize: 24

        height: 32
        width: parent.width

        horizontalAlignment: Label.AlignHCenter

        text: "Choose players"
      }

      ListView {
        id: playerSelector

        property var selectedNames: []

        clip: true

        width: parent.width

        anchors.top: playerLabel.bottom
        anchors.bottom: parent.bottom
        anchors.margins: 9

        boundsBehavior: ListView.StopAtBounds
        spacing: 9

        model: ListModel {
          id: playerListModel

          ListElement {
            name: "Max van Gerwen"
          }

          ListElement {
            name: "Jes Humphreys"
          }

          ListElement {
            name: "Simone Clayton"
          }

          ListElement {
            name: "Rasmus Smith"
          }

          ListElement {
            name: "Hjalte Van Veen"
          }

          ListElement {
            name: "Bjarke Anderson"
          }

          ListElement {
            name: "Ewelina Ratajski"
          }

          ListElement {
            name: "Laila Aspinal"
          }

          ListElement {
            name: "Lars Wright"
          }

          ListElement {
            name: "Benjamin Reus"
          }

          ListElement {
            name: "Storm Gates"
          }
        }

        delegate: Rectangle {
          color: playerSelector.selectedNames.includes(name) ? Qt.rgba(24, 24, 24, .5) : Qt.rgba(24, 24, 24, .3)
          radius: 9

          height: 64
          width: ListView.view.width

          Text {
            id: delegateText

            color: "lightgray"
            font.pixelSize: 28

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            anchors.fill: parent
            anchors.margins: 9

            text: name
          }

          MouseArea {
            anchors.fill: parent

            onClicked: {
              const selected = playerSelector.selectedNames;
              if (selected.includes(name)) {
                playerSelector.selectedNames = selected.filter(n => n !== name);
                parent.color = Qt.rgba(24, 24, 24, .3);
              } else {
                selected.push(name);
                parent.color = Qt.rgba(24, 24, 24, .5);
              }
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

    labelSize: 28
    label: qsTr("Start game")

    width: setupPage.isLandscape() ? 192 : parent.width
    height: 64

    onClicked: {
      if (setupPage.initializeController())
        setupPage.requestTournamentPage();
    }
  }
}
