import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Rectangle {
        color: "black"

        Image {
                source: "qrc:/pictures/Ressources/fck.png"
                x: parent.width / 2 - width / 2
                y: 5
                width: 150
                height: 150
        }

        Image {
                source: "qrc:/pictures/Ressources/pngfuel.com.png"
                x: parent.width / 2 - 175
                y: 5
                width: 130
                height: 130
        }

        Image {
                source: "qrc:/pictures/Ressources/tuborgclassic.png"
                x: parent.width / 2 + 25
                y: 25
                width: 130
                height: 130
                rotation: 25
        }

        Image {
                id: anti1964
                clip: true
                y: parent.height - height * 0.9
                x: -56
                scale: 0.7
                rotation: 12
                Layout.alignment: Qt.AlignHCenter
                source: "qrc:/pictures/Ressources/anti1964.webp"
        }

        Image {
                y: parent.height - height
                x: parent.width - width * 0.9
                rotation: -12
                source: "qrc:/pictures/Ressources/S12.png"
        }
}
