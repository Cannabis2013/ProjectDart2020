import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
        Button {
                text: "Menu"
                height: parent.height
                width: 90
                flat: true
                font.pointSize: 18
                font.weight: Font.Bold
                onClicked: menuRequest()
        }
}
