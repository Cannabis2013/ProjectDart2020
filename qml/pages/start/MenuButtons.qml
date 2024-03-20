import QtQuick 2.15
import QtQuick.Controls 2.15

Column {
        spacing: 5

        width: 192
        height: 48 * 5 + 20

        Button {
                flat: true
                font.pointSize: 24
                width: 192
                height: 48
                text: "Classic 1v1"
                onClicked: setupGameClicked()
        }

        Button {
                flat: true
                font.pointSize: 24
                width: 192
                height: 48
                text: "Resume game"
                onClicked: {
                        dartsInitializer.initFromStorage()
                        requestTournamentPage()
                }
        }

        Button {
                flat: true
                font.pointSize: 24
                width: 192
                height: 48
                text: "About"
                onClicked: requestAboutPage()
        }

        Button {
                flat: true
                font.pointSize: 24
                width: 192
                height: 48
                text: "Quit"
                onClicked: Qt.quit()
        }
}
