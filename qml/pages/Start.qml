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
    color: Qt.rgba(0,0,0,1)

    anchors.bottom: parent.bottom

    width: parent.width
    height: 64*2

    GridLayout{
      columns: 2
      rows: 2

      anchors.fill: parent

      Button {
        Layout.alignment: Qt.AlignHCenter

        font.pointSize: 16

        text: "Play"

        onClicked: requestSetupPage()
      }

      Button {
        Layout.alignment: Qt.AlignHCenter

        font.pointSize: 16

        text: "Resume"

        onClicked: {
          dartsInitializer.initFromStorage()
          requestTournamentPage()
        }
      }

      Button {
        Layout.alignment: Qt.AlignHCenter

        font.pointSize: 16

        text: "About"

        onClicked: requestAboutPage()
      }

      Button {
        Layout.alignment: Qt.AlignHCenter

        font.pointSize: 16

        text: "Quit"

        onClicked: Qt.quit()
      }
    }
  }

  Component.onCompleted: forceActiveFocus()
}
