import QtQuick 6.0
import QtQuick.Controls 2.12

ApplicationWindow {
        id: applicationWindow

        visible: true

        minimumHeight: 640
        minimumWidth: 400

        title: qsTr("Dart2020")

        PageLoader {
                id: mainPage
                anchors.fill: parent
        }
}
