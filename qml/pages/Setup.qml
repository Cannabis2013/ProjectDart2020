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
      enabled: selectedInfo.countIndex > 0
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
  background: Rectangle{
    anchors.fill: parent
    color: "#1f1f1f"
  }

  QtObject{
    id: selectedInfo
    property int countIndex: 0
    property var placeIndexes: []
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
  Item{
    id: listViewControls
    anchors{
      top: Script.isLandscape() ? parent.top : controlsContainer.bottom
      right: parent.right
      topMargin: 8
      left: Script.isLandscape() ? parent.horizontalCenter : parent.left
    }
    height: 48
    Text{
      id: firstIndex
      anchors{
        left: parent.left
        leftMargin: 8
      }
      height: parent.height
      width: 128
      color: "lightgray"
      font.pixelSize: 24
      verticalAlignment: Text.AlignVCenter
    }

    PushButton{
      label: "Unselect all"
      enabled: selectedInfo.countIndex > 0
      width: 128
      height: 32
      anchors {
        verticalCenter: parent.verticalCenter
        right: parent.right
        rightMargin: 8
      }
      onClicked: Script.unSelectAll()
    }
  }

  ListView {
    id: playersListView
    anchors{
      top: listViewControls.bottom
      right: parent.right
      bottom: parent.bottom
      topMargin: 8
      left: Script.isLandscape() ? parent.horizontalCenter : parent.left
    }
    clip: true
    spacing: 1
    reuseItems: true
    maximumFlickVelocity: 2500000
    boundsBehavior: ListView.StopAtBounds
    model: ListModel {
      id: playerListModel
    }
    QtObject{
      id: colors
      readonly property color normal: "#2f2f2f"
      readonly property color selected: "#4b4b4b"
    }

    delegate: Rectangle {
      id: playerDelegate
      required property string name
      required property int index
      required property bool selected
      required property int placeIndex
      height: 64
      width: ListView.view.width
      color: playerDelegate.selected ? colors.selected : colors.normal
      Text{
        id: orderId
        anchors {left: parent.left}
        width: 64
        height: parent.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: playerDelegate.placeIndex > 0 ? playerDelegate.placeIndex : ""
        font.pixelSize: 36
        font.weight: Font.Bold
        color: "lightgray"
      }
      Text {
          id: playerName
          anchors {
            left: parent.left;
            right: parent.right;
            top: parent.top;
            bottom:parent.bottom;
          }
          color: "lightgray"
          font.pixelSize: 24
          verticalAlignment: Text.AlignVCenter
          horizontalAlignment: Text.AlignHCenter
          text: playerDelegate.name
          MouseArea {
              anchors.fill: parent
              onClicked: Script.handlePlayerClicked(playerDelegate.index)
          }
      }
    }
  }
  Component.onCompleted: Script.init()
}
