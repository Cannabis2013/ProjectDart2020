import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

Rectangle{
    id: body

    color: "transparent"

    property color itemTextColor: "black"
    onItemTextColorChanged: listView.itemTextColor = itemTextColor

    property int itemFontSize: 10
    onItemFontSizeChanged: listView.itemFontSize = itemFontSize

    property color itemSelectedBackgroundColor: "white"
    onItemSelectedBackgroundColorChanged: listView.itemSelectedBackgroundColor = itemSelectedBackgroundColor

    property color itemSelectedtextColor: "black"
    onItemSelectedtextColorChanged: listView.itemSelectedtextColor = itemSelectedtextColor

    property int itemHeight: 50
    onItemHeightChanged: listView.itemHeight = itemHeight

    property int itemWidth : body.width
    onItemWidthChanged: listView.itemWidth = itemWidth

    property color itemHoveredColor: "transparent"
    onItemHoveredColorChanged: listView.itemHoveredColor = itemHoveredColor

    property color hoveredItemTextColor: "blue"
    onHoveredItemTextColorChanged: listView.hoveredItemTextColor = hoveredItemTextColor

    property color itemBackgroundColor: "transparent"
    onItemBackgroundColorChanged: listView.itemBackgroundColor = itemBackgroundColor

    function addItem(firstName, lastName, eMail, id){
        listView.addItem(firstName,lastName,eMail,id);
    }

    clip: true
    GridLayout
    {
        id: bodyLayout

        anchors.fill: parent

        rows:2
        columns: 2

        Label{

            Layout.row: 0
            Layout.column: 0
            text: "Pick players"
            font.pointSize: 24

            Layout.fillWidth: true

            horizontalAlignment: Qt.AlignHCenter
        }

        MyListView {
            id: listView

            itemFontSize: body.itemFontSize
            itemTextColor: body.itemTextColor

            itemSelectedtextColor: body.itemSelectedtextColor
            itemSelectedBackgroundColor: body.itemSelectedBackgroundColor

            itemHeight: body.itemHeight
            itemWidth: body.itemWidth

            Layout.row: 1
            Layout.column: 0

            Layout.fillWidth: true
            Layout.fillHeight: true

            PropertyAnimation on width {
                from: body.width / 2
                to: body.width

                duration: 300

                easing.type: Easing.OutBounce
            }
        }
    }
}
