import QtQuick 2.15
import QtQuick.Controls 2.12

ApplicationWindow {
        id: applicationWindow

        readonly property int defaultPageContentWidth: 512

        visible: true
        color: "black"

        minimumHeight: 640
        minimumWidth: 400

        title: qsTr("Dart2020")
        function destructor() {
                Qt.quit()
        }
        Item {
                id: keyListener
                anchors.fill: parent
                focus: true
                Keys.onPressed: {
                        if (event.key === Qt.Key_Q && event.modifiers & Qt.ControlModifier) {
                                destructor()
                                event.accepted = true
                        } else if (event.key === Qt.Key_Back) {
                                mainPage.backPushed()
                                event.accepted = true
                        }
                }
        }

        PageLoader {
                id: mainPage
                anchors.fill: parent
        }
}
