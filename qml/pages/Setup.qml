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

    PushButton{
      id: startButton

      onClicked: {
        if (Script.initializeController())
          setupPage.requestTournamentPage();
      }

      enabled: false
      height: 48
      width: 96
      anchors{
        right: parent.right
        verticalCenter: parent.verticalCenter
        rightMargin: 8
      }
      labelSize: 24
      label: "Start"
    }
  }
  padding: 9
  background: Rectangle{
    anchors.fill: parent
    color: "#1f1f1f"
  }

  QtObject{
    id: selectedInfo

    property int count: 0
    onCountChanged: startButton.enabled = count > 0
  }
  Item {
    id: controlsContainer

    height: Script.isLandscape() ? parent.height : 160
    anchors{
      top: parent.top
      right: Script.isLandscape() ? parent.horizontalCenter : parent.right
      left: parent.left
      margins: 8
    }
    ValueSelector {
      id: initialScoreSelector

      anchors{
        bottom: openingSelector.top
        horizontalCenter: parent.horizontalCenter
        margins: 8
      }
      width: Script.isLandscape() ? 384 : parent.width
      label: qsTr("Initial remaining:")
      model: [101, 201, 301, 501]
      currentIndex: 3
    }
    ValueSelector {
      id: openingSelector

      anchors{
        verticalCenter: parent.verticalCenter
        horizontalCenter: parent.horizontalCenter
      }
      width: Script.isLandscape() ? 384 : parent.width
      label: qsTr("Opens with:")
      model: ["None", "Number", "Double", "Tripple"]
    }
    ValueSelector {
      id: closeningSelector

      anchors{
        top: openingSelector.bottom
        horizontalCenter: parent.horizontalCenter
        margins: 8
      }
      width: Script.isLandscape() ? 384 : parent.width
      label: qsTr("Close with:")
      currentValue: "Double"
      model: ["None", "Number", "Double"]
    }
  }
  ListView {
    id: playersListView

    anchors{
      top: Script.isLandscape() ? parent.top : controlsContainer.bottom
      right: parent.right
      bottom: parent.bottom
      left: Script.isLandscape() ? parent.horizontalCenter : parent.left
      margins: 8
    }
    clip: true
    reuseItems: true
    maximumFlickVelocity: 2500000
    boundsBehavior: ListView.StopAtBounds
    model: ListModel {
      id: playerListModel
    }

    QtObject{
      id: colors

      readonly property color normal: "#2f2f2f"
      readonly property color selected: "#3f3f3f"
    }

    delegate: Item {
      id: playerDelegate

      required property string name
      required property int index
      required property bool selected
      required property int placeIndex

      height: 64
      width: ListView.view.width

      Rectangle{
        anchors{
          fill: parent
          margins: 3
        }
        color: playerDelegate.selected ? colors.selected : colors.normal
      }
      Text {
          id: delegateText
          anchors {fill: parent;margins: 8}
          color: "lightgray"
          font.pixelSize: 24
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
  Component.onCompleted: Script.init()
}
