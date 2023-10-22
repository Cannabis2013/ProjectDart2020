import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

Rectangle {
        color: "transparent"

        signal backClicked
        signal acceptClicked

        property string backButtonTitle: "back"
        onBackButtonTitleChanged: backButton.text = backButtonTitle
        property string acceptButtonTitle: "accept"
        onAcceptButtonTitleChanged: acceptButton.text = acceptButtonTitle

        GridLayout {
                anchors.fill: parent
                Button {
                        id: backButton
                        Layout.alignment: Qt.AlignRight
                        Layout.fillHeight: true
                        width: 64
                        text: backButtonTitle
                        onClicked: backClicked()
                }

                Button {
                        id: acceptButton
                        Layout.alignment: Qt.AlignLeft
                        Layout.fillHeight: true
                        width: 64
                        text: acceptButtonTitle
                        onClicked: acceptClicked()
                }
        }
}
