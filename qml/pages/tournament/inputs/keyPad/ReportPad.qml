import QtQuick 2.15

Pad {
        onPressed: scale = 0.8
        onReleased: scale = 1
        Image {
                anchors.centerIn: parent
                source: "qrc:/pictures/Ressources/Pictures/upArrow.png"
                width: 52
                height: 41
                rotation: 90
        }
}
