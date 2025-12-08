import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts
import "../components"

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
    opacity: .5
  }

  PushButton {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: resumeButton.top
    anchors.bottomMargin: 8
    labelSize: 24
    label: "Play"
    width: 128
    onClicked: requestSetupPage()
  }

  PushButton {
    id: resumeButton
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.verticalCenter
    anchors.bottomMargin: 4
    labelSize: 24
    label: "Resume"
    width: 128
    onClicked: {
      dartsInitializer.initFromStorage()
      requestTournamentPage()
    }
  }

  PushButton {
    id: aboutButton
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.verticalCenter
    anchors.topMargin: 4
    labelSize: 24
    label: "About"
    width: 128
    onClicked: requestAboutPage()
  }

  PushButton {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: aboutButton.bottom
    anchors.topMargin: 8
    labelSize: 24
    width: 128
    label: "Quit"
    onClicked: Qt.quit()
  }

  Component.onCompleted: forceActiveFocus()
}
