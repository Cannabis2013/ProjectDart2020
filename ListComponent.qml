import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13

Rectangle{
    id: body

    clip: true

    signal itemClicked(int index)
    signal itemSelected(int index)
    signal requestUpdate

    property double hoveredSizeScale: 0.90
    onHoveredSizeScaleChanged: listItem.hoveredSizeScale = hoveredSizeScale
    property double selectedSizeScale: 0.98
    onSelectedSizeScaleChanged: listItem.selectedSizeScale = selectedSizeScale
    property bool enableHover: listItem.enableHover = enableHover
    property bool allowCheckState: false
    onAllowCheckStateChanged: listItem.isCheckable = allowCheckState
    property bool instantSelectEnabled: false
    onInstantSelectEnabledChanged: listItem.noDelayPressSelect = instantSelectEnabled
    property bool allowMultipleSelections: false
    property string componentTitle: "Title"
    onComponentTitleChanged: labelTitle.text = componentTitle
    property color backgroundColor: "white"
    onBackgroundColorChanged: backgroundRect.color = body.backgroundColor
    property color titleBackground: "transparent"
    onTitleBackgroundChanged: labelTitle.backgroundColor = titleBackground
    property color labelTextColor: "black"
    onLabelTextColorChanged: labelTitle.fontColor = labelTextColor
    // General item properties
    // Item font/color/background properties
    property color itemTitleTextColor: "black"
    onItemTitleTextColorChanged: listItem.itemTextColor = itemTextColor
    property color itemDescriptionFontColor: "white"
    onItemDescriptionFontColorChanged: listItem.descriptionFontColor = itemDescriptionFontColor
    property int itemTitleFontSize: 10
    onItemTitleFontSizeChanged: listItem.titleFontSize = itemTitleFontSize
    property int itemDescriptionFontSize: 8
    onItemDescriptionFontSizeChanged: listItem.descriptionFontSize = itemDescriptionFontSize
    property color itemDescriptionBackgroundColor : "transparent"
    onItemDescriptionBackgroundColorChanged: listItem.descriptionBackgroundColor = itemDescriptionBackgroundColor
    property color itemTitleBackgroundColor: "transparent"
    onItemTitleBackgroundColorChanged: listItem.labelBackgroundColor = itemTitleBackgroundColor
    // Item background properties
    property color itemSelectedBackgroundColor: "white"
    onItemSelectedBackgroundColorChanged: listItem.selectedColor = itemSelectedBackgroundColor
    property color itemHoveredColor: itemBackgroundColor
    onItemHoveredColorChanged: listItem.itemHoveredColor = itemHoveredColor
    property color itemSelectedtextColor: "black"
    onItemSelectedtextColorChanged: listItem.selectedTextColor = itemSelectedtextColor
    property double itemBackgroundOpacity: 1
    onItemBackgroundOpacityChanged: listItem.backgroundOpacitity = itemBackgroundOpacity
    // Item geometry properties
    property int itemRoundedCorners: 0
    onItemRoundedCornersChanged: listItem.radius = itemRoundedCorner
    // Item size properties
    property double itemWidthScale: 0.95
    onItemWidthScaleChanged: body.itemWidth = body.width *body.itemWidthScale
    property int itemHeight: 50
    onItemHeightChanged: listItem.height = itemHeight
    property int itemWidth : body.width * itemWidthScale
    onItemWidthChanged: listItem.width = itemWidth
    property color hoveredItemTextColor: "blue"
    onHoveredItemTextColorChanged: listItem.hoveredItemTextColor = hoveredItemTextColor
    property color itemBackgroundColor: "transparent"
    onItemBackgroundColorChanged: listItem.itemBackgroundColor = itemBackgroundColor

    property color itemImageBackgroundColor: "transparent"
    onItemImageBackgroundColorChanged: listItem.imageBackgroundColor = itemImageBackgroundColor

    property url itemImageUrl: ""
    onItemImageUrlChanged: listItem.logoUrl = itemImageUrl

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

    Rectangle{
        id: backgroundRect
        anchors.fill: parent
        color: body.backgroundColor
        opacity: 0.1
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
            backgroundColor: body.titleBackground
            fontColor: body.labelTextColor
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

                onClicked: itemClicked(index)
                onCheckedChanged: itemSelected(index)

                titleFontSize: body.itemTitleFontSize
                titleFontColor: body.itemTitleTextColor
                descriptionFontSize: body.itemDescriptionFontSize
                descriptionFontColor: body.itemDescriptionFontColor
                isCheckable: allowCheckState
                hoveredColor: body.itemHoveredColor
                selectedColor: body.itemSelectedBackgroundColor
                selectedTextColor: body.itemSelectedtextColor
                height: body.itemHeight
                width: body.itemWidth
                backgroundColor: body.itemBackgroundColor
                radius: body.itemRoundedCorners
                logoUrl: body.itemImageUrl
                noDelayPressSelect: body.instantSelectEnabled
                labelBackgroundColor: body.itemTitleBackgroundColor
                imageBackgroundColor: body.itemImageBackgroundColor
                descriptionBackgroundColor: body.itemDescriptionBackgroundColor

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
