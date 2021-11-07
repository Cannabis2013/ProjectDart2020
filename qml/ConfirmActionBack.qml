import QtQuick 2.0
Rectangle {
    color: "transparent"
    Image{
        anchors.fill: parent
        source: "qrc:/pictures/Ressources/s12_1.jpg"
    }
    Image {
        x: parent.width / 2 - 48
        y: parent.height / 4 - 48
        width: 96
        height: 96
        source: "qrc:/pictures/Ressources/fck_jersey_logo.png"
    }
}
