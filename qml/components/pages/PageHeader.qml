import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import "../../components/buttons"

Rectangle {
        signal backButtonClicked
        height: 64
        color: "black"
        GridLayout {
                anchors.fill: parent
                flow: GridLayout.LeftToRight
                Rectangle {
                        width: 24
                }

                PushButton {
                        text: "Back"
                        width: 64
                        height: 48
                        Layout.alignment: Qt.AlignVCenter
                        onClicked: backButtonClicked()
                }

                Rectangle {
                        Layout.fillWidth: true
                }
        }
}
