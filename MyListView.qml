import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

ListView
{
    property int itemFontSize: 12
    onItemFontSizeChanged: listItem.fontSize = itemFontSize

    property color itemSelectedColor: "white"
    onItemSelectedColorChanged: listItem.checkedColor = itemSelectedColor

    Layout.fillWidth: true
    Layout.fillHeight: true

    clip: true

    spacing: 1

    function addItem(firstName, lastName, eMail, id = 0)
    {
        listModel.append({"firstName" : firstName,"lastName" : lastName, "email" : eMail, "uuid" : id});
    }
    
    
    model: ListModel {
        id: listModel
    }

    
    delegate: PushButton{
        id: listItem

        fontSize: itemFontSize

        anchors.bottomMargin: 15

        clip: true

        isCheckable: true

        hoveredColor: "transparent"
        hoveredTextColor: "blue"

        checkedColor: itemSelectedColor

        height: 70
        width: parent.width

        backgroundColor: "transparent"

        text: "Full name: " + firstName + " " + lastName + "\n" +
              "E-mail: " + email

        PropertyAnimation on width {
            from: 0
            to: parent.width

            duration: 300

            easing.type: Easing.OutBounce
        }
    }
}
