import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts
import "../components"
import "../scripts/startPage.js" as Script

Page {
  id: startPage

  signal requestTournamentPage
  signal requestCalculator
  signal requestAboutPage
  signal requestSetupPage
  signal customizeMode

  ImageCarousel {
    id: imageCarousel

    x: Script.carouselRect().x
    y: Script.carouselRect().y
    height: Script.carouselRect().h
    width: Script.carouselRect().w
    sources: Script.carouselSources()
  }

  Text{
    text: "Created with"
    height: 64
    anchors {top: logoImage.top;right: logoImage.left;rightMargin: 32}
    color: "lightgray"
    font.pixelSize: 24
  }

  Image {
    id: logoImage
    source: "qrc:/pictures/Ressources/Pictures/qt_logo.png"
    anchors {bottom: parent.bottom;right: parent.right;margins: 32}
    width: 64
    height: 64
    fillMode: Image.PreserveAspectFit
  }

  ColumnLayout{
    id: buttonsLayout
    x: Script.buttonsLayoutRect().x
    y: Script.buttonsLayoutRect().y
    spacing: 8
    width: Script.buttonsLayoutRect().w
    height: Script.buttonsLayoutRect().h
    PushButton {
      labelSize: 24
      label: "Play"
      Layout.fillWidth: true
      Layout.fillHeight: true
      onClicked: startPage.requestSetupPage()
    }

    PushButton {
      id: resumeButton
      labelSize: 24
      label: "Resume"
      Layout.fillWidth: true
      Layout.fillHeight: true
      onClicked: {
        dartsInitializer.initFromStorage()
        startPage.requestTournamentPage()
      }
    }

    PushButton{
      id: calculatorButton
      labelSize: 24
      label: "Udregner"
      Layout.fillWidth: true
      Layout.fillHeight: true
      onClicked: startPage.requestCalculator()
    }

    PushButton {
      id: aboutButton
      labelSize: 24
      label: "About"
      Layout.fillWidth: true
      Layout.fillHeight: true
      onClicked: startPage.requestAboutPage()
    }

    PushButton {
      labelSize: 24
      Layout.fillWidth: true
      Layout.fillHeight: true
      label: "Quit"
      onClicked: Qt.quit()
    }
  }
}
