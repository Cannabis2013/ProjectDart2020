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

  background: Rectangle{
    anchors.fill: parent
    color: "#1f1f1f"
  }

  ImageCarousel {
    id: imageCarousel
    x: 0
    y: startPage.height - height
    height: Script.carouselRect().h
    width: Script.carouselRect().w
    sources: Script.carouselSources()
    visible: !Script.isPortrait()
  }
  Text{
    text: "QtDart"
    font.pixelSize: Script.isPortrait() ? 70 : 128
    x: Script.isPortrait() ? 0 : 32
    y: Script.isPortrait() ? 16 : 32
    width: Script.isPortrait() ? parent.width : 384
    height: Script.isPortrait() ? 36 : 64
    color: "lightgray"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
  }
  Text{
    text: "Created with"
    height: 64
    anchors {top: logoImage.top;right: logoImage.left;rightMargin: 16}
    color: "lightgray"
    font.pixelSize: 24
  }
  Image {
    id: logoImage
    source: "qrc:/Ressources/qt_logo.png"
    anchors {bottom: parent.bottom;right: parent.right;margins: 32}
    width: 64
    height: 64
  }
  ColumnLayout{
    id: buttonsLayout
    x: Script.isPortrait() ? (startPage.width - width) / 2 :
                      startPage.width - width - 32
    y: startPage.height > 480 ? (startPage.height - height) / 2 : 32
    spacing: 8
    width: 200
    height: Script.isPortrait() ? 288 : 200
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
