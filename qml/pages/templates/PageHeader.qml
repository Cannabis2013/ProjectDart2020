import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Rectangle {
        signal backButtonClicked
        signal backButtonLongClicked

        property string buttonText: headerButton.text
        onButtonTextChanged: headerButton.text = buttonText

        property string pageTitle: pageTitleComp.text
        onPageTitleChanged: pageTitleComp.text = pageTitle

        height: 64
        color: "transparent"

        RowLayout {
                anchors.fill: parent

                Button {
                        id: headerButton
                        flat: true
                        font.pointSize: 24
                        font.weight: Font.Bold
                        text: "Back"
                        width: 48
                        height: 32
                        Layout.alignment: Qt.AlignVCenter
                        onClicked: backButtonClicked()
                        onPressAndHold: backButtonLongClicked()
                }

                Text {
                        id: pageTitleComp
                        font.pointSize: 20
                        color: "white"
                        Layout.fillWidth: true
                        height: 32
                        verticalAlignment: Text.AlignVCenter
                }
        }
}
