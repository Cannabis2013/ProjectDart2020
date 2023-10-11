import QtQuick 2.0
import QtQuick.Layouts 1.3

import "../../components/pages"
import "../../components/buttons"

BlackPageWithHeader {
        id: confirmPage

        signal acceptClicked

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom
                Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: qsTr("Are you sure? Any saved progress will be lost.")
                        font.pointSize: 24
                        font.weight: Font.Bold
                        Layout.fillHeight: true
                        Layout.maximumWidth: confirmPage.width * 0.8
                        wrapMode: Text.WordWrap
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                }

                Rectangle {
                        color: "transparent"
                        height: 64
                        Layout.alignment: Qt.AlignHCenter
                        width: 300
                        GridLayout {
                                anchors.fill: parent
                                PushButton {
                                        Layout.fillHeight: true
                                        width: 128
                                        text: "Back"
                                        onClicked: backClicked()
                                }

                                PushButton {
                                        Layout.fillHeight: true
                                        width: 128
                                        text: "Don't care."
                                        onClicked: acceptClicked()
                                }
                        }
                }

                Rectangle {
                        height: 16
                }
        }
}
