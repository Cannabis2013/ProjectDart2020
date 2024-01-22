import QtQuick 2.0
import QtQuick.Layouts 1.3
import "playersSection.js" as Scripts

Image {
        id: turnRect

        height: 32
        width: 32

        Behavior on x {
                NumberAnimation {
                        duration: 200
                }
        }

        source: "qrc:/pictures/Ressources/Pictures/up_arrow.png"
}
