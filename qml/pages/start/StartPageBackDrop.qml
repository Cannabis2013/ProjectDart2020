import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
        anchors.fill: parent

        Image {
                source: "qrc:/pictures/Ressources/Pictures/gerwen.png"
                height: width * 1.1
                width: 128
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 12
        }

        Image {
                source: "qrc:/pictures/Ressources/Pictures/dartsplate.png"
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: 80
                anchors.leftMargin: 40
                width: height * 1.4
                height: 112
                fillMode: Image.PreserveAspectFit
        }

        Image {
                source: "qrc:/pictures/Ressources/Pictures/SnakeBite.png"
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.topMargin: 64
                anchors.rightMargin: 12
                height: width / 1.777777778
                width: 192
                fillMode: Image.PreserveAspectFit
        }

        Text {
                text: qsTr("Created by: Martin Hansen")
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.rightMargin: 12
                anchors.bottomMargin: 12
                font.pointSize: 12
                color: "white"
        }
}
