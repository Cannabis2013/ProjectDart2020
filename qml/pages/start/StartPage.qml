import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "../templates"
import "startPage.js" as Scripts

Page {
        id: startPage

        signal requestTournamentPage
        signal requestAboutPage
        signal setupGameClicked

        focus: true

        Keys.onPressed: event => {
                                if (event.key === Qt.Key_Back) {
                                        event.accepted = true
                                }
                        }

        StartPageBackDrop {
                visible: Scripts.isPortrait()
        }

        StartMenuButtons {
                id: gridLayout
                anchors.centerIn: parent
        }

        Component.onCompleted: forceActiveFocus()
}
