import QtQuick 2.15
import QtQuick.Layouts 1.3
import "../templates"

BlackPageWithHeader {
        pageTitle: "About"
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
                                Layout.fillWidth: true
                                height: 64
                                verticalAlignment: Text.AlignVCenter
                                font.pointSize: 32
                                font.weight: Font.Bold
                                text: qsTr("About DartApp")
                                color: "white"
                        }

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

        Component.onCompleted: {
                const xhr = new XMLHttpRequest
                xhr.open("GET", "qrc:/data/Ressources/aboutContent.dat")
                xhr.onreadystatechange = function () {
                        if (xhr.readyState === XMLHttpRequest.DONE)
                                aboutText.text = xhr.responseText
                }
                xhr.send()
        }
}
