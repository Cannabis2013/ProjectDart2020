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

  Column {
    anchors.centerIn: parent
    spacing: 5

    width: 192
    height: 48 * 4 + 20

    Button {
      font.pointSize: 16
      width: 192
      height: 48
      text: "Play"
      onClicked: requestSetupPage()
    }

    Button {
      font.pointSize: 16
      width: 192
      height: 48
      text: "Resume game"
      onClicked: {
        dartsInitializer.initFromStorage()
        requestTournamentPage()
      }
    }

    Button {
      font.pointSize: 16
      width: 192
      height: 48
      text: "About"
      onClicked: requestAboutPage()
    }

    Button {
      font.pointSize: 16
      width: 192
      height: 48
      text: "Quit"
      onClicked: Qt.quit()
    }
  }

  Component.onCompleted: forceActiveFocus()
}
