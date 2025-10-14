import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts

Page {
  id: startPage

  signal requestTournamentPage
  signal requestAboutPage
  signal requestSetupPage
  signal customizeMode

  focus: true

  Image{
    anchors.fill: parent
    source: "qrc:/pictures/Ressources/Pictures/dart.png"
    fillMode: Image.PreserveAspectCrop
  }

  Rectangle {
    radius: 20

    color: Qt.rgba(0,0,0,.8)

    anchors.centerIn: parent

    width: 256
    height: 384

    Button {
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.bottom: resumeButton.top
      anchors.bottomMargin: 8

      font.pointSize: 16

      text: "Play"

      onClicked: requestSetupPage()
    }

    Button {
      id: resumeButton

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.bottom: parent.verticalCenter
      anchors.bottomMargin: 4

      font.pointSize: 16

      text: "Resume"

      onClicked: {
        dartsInitializer.initFromStorage()
        requestTournamentPage()
      }
    }

    Button {
      id: aboutButton

      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: parent.verticalCenter
      anchors.topMargin: 4

      font.pointSize: 16

      text: "About"

      onClicked: requestAboutPage()
    }

    Button {
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: aboutButton.bottom
      anchors.topMargin: 8

      font.pointSize: 16

      text: "Quit"

      onClicked: Qt.quit()
    }
  }

  Component.onCompleted: forceActiveFocus()
}
