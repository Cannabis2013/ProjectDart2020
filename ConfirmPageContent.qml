import QtQuick 2.0
import QtQuick.Layouts 1.3

Page{
    id: pageBody

    pageTitle: qsTr("Confirm your action")

    signal acceptClicked
    signal cancelClicked

    pageContent: Content {
        id: contentBody

        GridLayout{
            anchors.fill: parent
            flow: GridLayout.LeftToRight
            Rectangle{
                Layout.fillWidth: true
            }

            PushButton{
                id: cancelButton
                text: qsTr("Cancel")
                width: 128
                height: 48
                fontSize: 20
                backgroundColor: "green"
                textColor: "white"
                Layout.alignment: Qt.AlignBottom | Qt.alignRight
                onClicked: {
                    pageBody.cancelClicked();
                    backButtonPressed();
                }
            }
            PushButton{
                id: acceptButton
                text: qsTr("Accept")
                width: 128
                height: 48
                fontSize: 20
                backgroundColor: "green"
                textColor: "white"
                Layout.alignment: Qt.AlignBottom | Qt.alignRight
                onClicked: {
                    pageBody.acceptClicked();
                    backButtonPressed();
                }
            }
        }
    }
}
