import QtQuick 6.0
import QtQuick.Layouts 1.3
import "../templates"

PageWithHeader {
        pageTitle: "About DartApp"
        GridLayout {
                anchors.fill: parent
                Rectangle {
                        width: 6
                }

                GridLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        flow: GridLayout.TopToBottom
                        Text {
                                id: aboutText
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                wrapMode: Text.WordWrap
                                font.pointSize: 16
                                onLinkActivated: Qt.openUrlExternally(link)
                                color: "white"
                        }
                }

                Rectangle {
                        width: 6
                }
        }

        Component.onCompleted: aboutText.text = fileHtml.aboutHtml()
}
