import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13

Rectangle{
    id: body

    color: "transparent"

    clip: true

    property bool allowCheckState: false
    onAllowCheckStateChanged: listItem.isCheckable = allowCheckState

    property bool instantSelectEnabled: false
    onInstantSelectEnabledChanged: listItem.noDelayPressSelect = instantSelectEnabled

    property bool allowMultipleSelections: false

    property string componentTitle: "Title"
    onComponentTitleChanged: labelTitle.text = componentTitle

    property color itemTextColor: "black"
    onItemTextColorChanged: listItem.itemTextColor = itemTextColor

    property int itemTitleFontSize: 12
    onItemTitleFontSizeChanged: listItem.titleFontSize = itemTitleFontSize

    property int itemDescriptionFontSize: 10
    onItemDescriptionFontSizeChanged: listItem.descriptionFontSize = itemDescriptionFontSize

    property color labelBackgroundColor: "lightgray"
    onLabelBackgroundColorChanged: listItem.labelBackgroundColor = labelBackgroundColor

    property color itemSelectedBackgroundColor: "white"
    onItemSelectedBackgroundColorChanged: listItem.selectedColor = itemSelectedBackgroundColor

    property color itemSelectedtextColor: "black"
    onItemSelectedtextColorChanged: listItem.selectedTextColor = itemSelectedtextColor

    property int itemRoundedCorners: 0
    onItemRoundedCornersChanged: listItem.radius = itemRoundedCorners

    property int itemHeight: 50
    onItemHeightChanged: listItem.height = itemHeight

    property int itemWidth : body.width
    onItemWidthChanged: listItem.width = itemWidth

    property color itemHoveredColor: "transparent"
    onItemHoveredColorChanged: listItem.itemHoveredColor = itemHoveredColor

    property color hoveredItemTextColor: "blue"
    onHoveredItemTextColorChanged: listItem.hoveredItemTextColor = hoveredItemTextColor

    property color itemBackgroundColor: "transparent"
    onItemBackgroundColorChanged: listItem.itemBackgroundColor = itemBackgroundColor

    property color imageBackgroundColor: "transparent"
    onImageBackgroundColorChanged: listItem.imageBackgroundColor = imageBackgroundColor

    property url itemDecorator: ""
    onItemDecoratorChanged: listItem.logoUrl = itemDecorator

    signal itemClicked(int index)
    signal itemSelected(int index)

    function clear(){
        listModel.clear();
    }

    function currentIndexes()
    {
        var cIndexes = [];
        var j = 0;
        for(var i = 0;i < listView.count;i++)
        {
            var item = listView.itemAtIndex(i);
            var itemState = item.state;
            if(itemState === "checked")
                cIndexes[j++] = i;
        }
        return cIndexes;
    }

    function unSelectAllItems()
    {
        for(var i = 0;i < listView.count;i++)
        {
            var item = listView.itemAtIndex(i);
            var itemState = item.state;
            if(itemState === "checked")
                item.state = "";
        }
    }

    function addItemModel(itemModel)
    {
        listModel.append(itemModel);
    }

    function removeItemModels(indexes)
    {
        var length = indexes.length;
        for(var i = 0;i < length;i++){
            var index = indexes[i];
            listModel.remove(index);
        }
    }
    layer.enabled: true

    layer.effect: OpacityMask{
        maskSource: Item {
            width: body.width
            height: body.height

            Rectangle{
                anchors.fill: parent
                radius: body.radius
            }
        }
    }

    GridLayout
    {
        id: bodyLayout

        anchors.fill: parent

        flow: GridLayout.TopToBottom

        LabelComponent {
            id: labelTitle
            Layout.fillWidth: true
            Layout.minimumHeight: 48
            fontSize: 24
            backgroundColor: "darkgray"
            text: componentTitle
        }

        ListView
        {
            id: listView
            clip: true
            spacing: 5

            Layout.fillHeight: true
            Layout.fillWidth: true
            model: ListModel {
                id: listModel
            }
            delegate: ListViewDelegate{
                id: listItem

                titleFontSize: body.itemTitleFontSize
                descriptionFontSize: body.itemDescriptionFontSize
                onClicked: itemClicked(index)
                isCheckable: allowCheckState

                hoveredColor: body.itemHoveredColor
                hoveredTextColor: body.hoveredItemTextColor
                selectedColor: body.itemSelectedBackgroundColor
                selectedTextColor: body.itemSelectedtextColor
                height: body.itemHeight
                width: body.itemWidth
                backgroundColor: body.itemBackgroundColor
                textColor: body.itemTextColor
                radius: body.itemRoundedCorners
                logoUrl: body.itemDecorator
                noDelayPressSelect: body.instantSelectEnabled
                labelBackgroundColor: body.labelBackgroundColor
                imageBackgroundColor: body.imageBackgroundColor

                title: {
                    if(type == "player")
                        return username;
                    else if(type == "tournament")
                    {
                        return tournamentTitle;
                    }
                }
                description: {
                    if(type == "player")
                        return "Mail: " + mail;
                    else
                        "Throws: " + Throws + " | Keypoint: " + KeyPoint + " | Playercount: " + playersCount;
                }

                x: parent.width / 2 - width / 2
            }
        }
    }
}
