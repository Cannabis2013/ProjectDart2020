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

    property color itemTextColor: "black"
    onItemTextColorChanged: listItem.textColor = itemTextColor

    property int itemFontSize: 12
    onItemFontSizeChanged: listItem.fontSize = itemFontSize

    property color itemSelectedBackgroundColor: "white"
    onItemSelectedBackgroundColorChanged: listItem.checkedBackgroundColor = itemSelectedBackgroundColor

    property color itemSelectedtextColor: "black"
    onItemSelectedtextColorChanged: listItem.checkedTextColor = itemSelectedtextColor

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
        var model = {"firstName" : firstName,"lastName" : lastName, "email" : eMail, "uuid" : id};
        listModel.append(model);
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

        checkedBackgroundColor: body.itemSelectedBackgroundColor
        checkedTextColor: body.itemSelectedtextColor

        height: body.itemHeight
        width: body.itemWidth

        backgroundColor: body.itemBackgroundColor
        textColor: body.itemTextColor

        text: "Full name: " + firstName + " " + lastName + "\n" +
              "E-mail: " + email

        x: parent.width / 2 - width / 2

    }
}
