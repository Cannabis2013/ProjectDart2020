import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

ListView
{
    id: body

    clip: true

    spacing: 1

    property int itemFontSize: 12
    onItemFontSizeChanged: listItem.fontSize = itemFontSize

    property color itemSelectedColor: "white"
    onItemSelectedColorChanged: listItem.checkedColor = itemSelectedColor

    property int itemHeight: 70
    onItemHeightChanged: listItem.height = itemHeight

    property int itemWidth : body.width
    onItemWidthChanged: listItem.width = itemWidth

    property color itemHoveredColor: "transparent"
    onItemHoveredColorChanged: listItem.hoveredColor = itemHoveredColor

    property color hoveredItemTextColor: "blue"
    onHoveredItemTextColorChanged: listItem.hoveredTextColor = hoveredItemTextColor

    property color itemBackgroundColor: "transparent"
    onItemBackgroundColorChanged: listItem.backgroundColor = itemBackgroundColor


    function addItem(firstName, lastName, eMail, id = 0)
    {
        listModel.append({"firstName" : firstName,"lastName" : lastName, "email" : eMail, "uuid" : id});
    }
    
    model: ListModel {
        id: listModel
    }
    
    delegate: PushButton{
        id: listItem

        clip: true

        fontSize: itemFontSize

        isCheckable: true

        hoveredColor: body.itemHoveredColor
        hoveredTextColor: body.hoveredItemTextColor
        checkedColor: itemSelectedColor

        height: body.itemHeight
        width: body.itemWidth

        x: parent.width / 2 - width / 2

        backgroundColor: body.itemBackgroundColor

        text: "Full name: " + firstName + " " + lastName + "\n" +
              "E-mail: " + email

        PropertyAnimation on width {
            from: 0
            to: body.itemWidth

            duration: 300

            easing.type: Easing.OutBounce
        }
    }
}
