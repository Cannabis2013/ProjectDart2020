import QtQuick 2.15
import QtQuick.Controls 2.12
import "../templates"
import "initScripts.js" as Scripts

PageWithHeader {
  signal requestTournamentPage

  padding: 9

  Button {
    id: goButton
    width: 128
    height: 48
    font.pointSize: 16
    anchors.horizontalCenter: initialScoreSelector.horizontalCenter
    text: "Go"
    onClicked: {
      Scripts.init()
      requestTournamentPage()
    }
  }

  ValueSelector {
    id: initialScoreSelector
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: goButton.bottom
    anchors.topMargin: 9
    label: "Initial score"
    model: [101, 201, 301, 501]
    currentIndex: 3
  }

  ValueSelector {
    id: playersCountSelector
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: initialScoreSelector.bottom
    anchors.topMargin: 9
    currentIndex: 1
    label: "Number of players"
    model: [1, 2, 3, 4, 5, 6, 7, 8]
  }

  ValueSelector {
    id: openingSelector
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: playersCountSelector.bottom
    anchors.topMargin: 9
    label: "Opening condition"
    model: ["None", "number", "double"]
  }

  ValueSelector {
    id: closeningSelector
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: openingSelector.bottom
    anchors.topMargin: 9
    label: "Closening condition"
    model: ["None", "number", "double"]
  }
}
