import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: applicationWindow
    visible: true
    color: "lightgray"

    x: 120
    y: 120

    width: 400
    height: 500

    title: qsTr("Dart2020")

    Component
    {
        id: mouseComponent
        MouseArea
        {
            onClicked: startLoader.sourceComponent = myStartPage
        }
    }

    Component
    {
        id: myStartPage
        StartPage{

            onStartGameRequest: {}
            onLoginPageRequest: {}

            labelColor: "#A54141"
            backgroundContentColor: "#A54141"

        }
    }

    Loader{
        id: startLoader

        anchors.fill: parent
        sourceComponent: myStartPage
        }


}

