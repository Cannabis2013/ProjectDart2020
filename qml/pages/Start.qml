import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts
import "../components"

Page {
  id: startPage

  signal requestTournamentPage
  signal requestCalculator
  signal requestAboutPage
  signal requestSetupPage
  signal customizeMode

  focus: true

  Image{
    anchors.fill: parent
    source: "qrc:/pictures/Ressources/Pictures/dart.png"
    fillMode: Image.PreserveAspectCrop
    opacity: .3
  }

  PushButton {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: resumeButton.top
    anchors.bottomMargin: 8
    labelSize: 28
    label: "Play"
    width: 144
    height: 64
    onClicked: requestSetupPage()
  }

  PushButton {
    id: resumeButton
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: calculatorButton.top
    anchors.bottomMargin: 4
    labelSize: 28
    label: "Resume"
    width: 144
    height: 64
    onClicked: {
      dartsInitializer.initFromStorage()
      requestTournamentPage()
    }
  }

  PushButton{
    id: calculatorButton
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.verticalCenter
    anchors.bottomMargin: 4
    labelSize: 28
    label: "Udregner"
    width: 144
    height: 64
    onClicked: requestCalculator()
  }

  PushButton {
    id: aboutButton
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.verticalCenter
    anchors.topMargin: 4
    labelSize: 28
    label: "About"
    width: 144
    height: 64
    onClicked: requestAboutPage()
  }

  PushButton {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: aboutButton.bottom
    anchors.topMargin: 8
    labelSize: 28
    width: 144
    height: 64
    label: "Quit"
    onClicked: Qt.quit()
  }

  Component.onCompleted: forceActiveFocus()
}
