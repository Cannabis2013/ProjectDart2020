import QtQuick 2.15
import QtQuick.Controls 2.15

Column {
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
