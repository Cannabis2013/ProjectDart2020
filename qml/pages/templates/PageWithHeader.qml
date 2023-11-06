import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Page {
        id: pageRect

        signal backClicked
        signal backLongClicked

        anchors.fill: parent

        focus: true
        Keys.onPressed: event => {
                                if (event.key === Qt.Key_Back) {
                                        event.accepted = true
                                }
                        }

        property string buttonText: "Back"
        onButtonTextChanged: pageButton.text = buttonText

        property string pageTitle: ""
        onPageTitleChanged: pageLabel.text = pageTitle

        header: Item {
                id: headerRect

                height: 64

                RowLayout {
                        anchors.fill: parent

                        Button {
                                id: pageButton
                                flat: true
                                font.pointSize: 24
                                font.weight: Font.Bold
                                text: pageRect.buttonText
                                width: 48
                                height: 32
                                Layout.alignment: Qt.AlignVCenter
                                onClicked: pageRect.backClicked()
                                onPressAndHold: pageRect.backLongClicked()
                        }

                        Text {
                                id: pageLabel
                                font.pointSize: 20
                                color: "white"
                                Layout.fillWidth: true
                                height: 32
                                verticalAlignment: Text.AlignVCenter
                        }
                }
        }
}
