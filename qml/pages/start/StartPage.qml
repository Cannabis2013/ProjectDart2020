import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "../templates"

Page {
        id: startPageContentBody

        signal requestTournamentPage
        signal requestAboutPage
        signal setupGameClicked

        focus: true

        Keys.onPressed: event => {
                                if (event.key === Qt.Key_Back) {
                                        event.accepted = true
                                }
                        }

        StartPageBackDrop {}

        StartMenuButtons {
                id: gridLayout
                anchors.centerIn: parent
        }

        Component.onCompleted: forceActiveFocus()
}
