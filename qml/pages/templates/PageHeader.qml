import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

import "../../components/buttons"

Rectangle {
        signal backButtonClicked

        property string buttonText: headerButton.text
        onButtonTextChanged: headerButton.text = buttonText

        property string pageTitle: pageTitleComp.text
        onPageTitleChanged: pageTitleComp.text = pageTitle

        height: 64
        color: "transparent"

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.LeftToRight
                Rectangle {
                        width: 6
                }

                PushButton {
                        id: headerButton
                        text: "Back"
                        width: 48
                        height: 32
                        radius: 12
                        Layout.alignment: Qt.AlignVCenter
                        onClicked: backButtonClicked()
                }

                Rectangle {
                        width: 6
                }

                Text {
                        id: pageTitleComp
                        text: "Page title"
                        font.pointSize: 20
                        color: "white"
                        Layout.fillWidth: true
                        height: 32
                }
        }
}
