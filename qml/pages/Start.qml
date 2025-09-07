import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3

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

  Rectangle{
    color: Qt.rgba(0,0,0,.75)

    width: parent.width
    height: 64

    Button {
      id: playButton

      x: parent.width / 4 - 64
      anchors.verticalCenter: parent.verticalCenter

      width: 128
      height: 48

      font.pointSize: 16


      text: "Play"

      onClicked: requestSetupPage()
    }

    Button {
      id: resumeButton

      x: parent.width * 3 / 4 - 64
      anchors.verticalCenter: parent.verticalCenter

      width: 128
      height: 48

      font.pointSize: 16

      text: "Resume"

      onClicked: {
        dartsInitializer.initFromStorage()
        requestTournamentPage()
      }
    }
  }

  Rectangle {
    color: Qt.rgba(0,0,0,.75)

    anchors.bottom: parent.bottom

    width: parent.width
    height: 64

    Button {
      x: parent.width / 4 - 64
      anchors.verticalCenter: parent.verticalCenter

      width: 128
      height: 48

      font.pointSize: 16

      text: "About"

      onClicked: requestAboutPage()
    }

    Button {
      x: parent.width * 3 / 4 - 64
      anchors.verticalCenter: parent.verticalCenter

      font.pointSize: 16

      width: 128
      height: 48

      text: "Quit"

      onClicked: Qt.quit()
    }
  }

  Component.onCompleted: forceActiveFocus()
}
