import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13

Rectangle{
    id: body

    color: "transparent"

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
    property color titleBackground: "darkgray"
    onTitleBackgroundChanged: labelTitle.backgroundColor = titleBackground
    property color itemTitleTextColor: "black"
    onItemTitleTextColorChanged: listItem.itemTextColor = itemTextColor
    property color itemDescriptionFontColor: "white"
    onItemDescriptionFontColorChanged: listItem.descriptionFontColor = itemDescriptionFontColor
    property int itemTitleFontSize: 12
    onItemTitleFontSizeChanged: listItem.titleFontSize = itemTitleFontSize
    property int itemDescriptionFontSize: 10
    onItemDescriptionFontSizeChanged: listItem.descriptionFontSize = itemDescriptionFontSize
    property color itemDescriptionBackgroundColor : "transparent"
    onItemDescriptionBackgroundColorChanged: listItem.descriptionBackgroundColor = itemDescriptionBackgroundColor
    property color itemTitleBackgroundColor: "lightgray"
    onItemTitleBackgroundColorChanged: listItem.labelBackgroundColor = itemTitleBackgroundColor
    property color itemSelectedBackgroundColor: "white"
    onItemSelectedBackgroundColorChanged: listItem.selectedColor = itemSelectedBackgroundColor
    property color itemSelectedtextColor: "black"
    onItemSelectedtextColorChanged: listItem.selectedTextColor = itemSelectedtextColor
    property int itemRoundedCorners: 0
    onItemRoundedCornersChanged: listItem.radius = itemRoundedCorner
    property int itemHeight: 50
    onItemHeightChanged: listItem.height = itemHeight
    property int itemWidth : body.width
    onItemWidthChanged: listItem.width = itemWidth
    property color itemHoveredColor: itemBackgroundColor
    onItemHoveredColorChanged: listItem.itemHoveredColor = itemHoveredColor
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
                descriptionFontSize: body.itemDescriptionFontSize
                isCheckable: allowCheckState
                hoveredColor: body.itemHoveredColor
                selectedColor: body.itemSelectedBackgroundColor
                selectedTextColor: body.itemSelectedtextColor
                height: body.itemHeight
                width: body.itemWidth
                backgroundColor: body.itemBackgroundColor
                titleFontColor: body.itemTitleTextColor
                descriptionFontColor: body.itemDescriptionFontColor
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
