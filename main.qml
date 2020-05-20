import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: applicationWindow
    visible: true
    color: "lightgray"
    width: 640
    height: 480
    title: qsTr("Dart2020")

    TextEdit
    {
        id: userNameBox
        text: qsTr("Enter your username")
    }
}
