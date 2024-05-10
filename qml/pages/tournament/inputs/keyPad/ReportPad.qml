import QtQuick 6.0

Pad {
        onPressed: scale = 0.8
        onReleased: scale = 1
        color: "orange"
        Image {
                anchors.centerIn: parent
                source: "qrc:/pictures/Ressources/Pictures/upArrow.png"
                width: 42
                height: 31
                rotation: 90
        }
}
