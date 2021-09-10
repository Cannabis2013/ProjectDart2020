import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13

import "tournamentListViewScripts.js" as TournamentListViewScripts

Rectangle{
    id: listComponentBody
    color: "transparent"
    clip: true
    // Signals
    signal addItem(var item)
    onAddItem: TournamentListViewScripts.addItemModel(item)
    signal removeItems(var indexes)
    onRemoveItems: TournamentListViewScripts.removeItemModels(indexes)
    signal itemClicked(int index)
    signal itemSelected(int index)
    signal unSelectAllItems()
    onUnSelectAllItems: TournamentListViewScripts.unSelectAll()
    signal clear()
    onClear: listModel.clear()
    signal requestUpdate
    // Properties
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
    onBackgroundColorChanged: backgroundRect.color = listComponentBody.backgroundColor
    // Title properties
    // Title backgroundcolor/opacity and title fontcolor
    property color titleBackground: "transparent"
    onTitleBackgroundChanged: labelTitle.backgroundColor = titleBackground
    property double titleBackgroundOpacity: 1
    onTitleBackgroundOpacityChanged: labelTitle.backOpacity = titleBackgroundOpacity
    property color titleTextColor: "black"
    onTitleTextColorChanged: labelTitle.fontColor = titleTextColor
    property url titleImageUrl: ""
    onTitleImageUrlChanged: labelTitle.imageUrl = titleImageUrl
    // Title font hoveredSizeScale:
    property int titleFontSize: 20
    onTitleFontSizeChanged: labelTitle.fontSize = titleFontSize
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
    // Label alignment properties
    property int horizontalLabelAlignment: Qt.AlignHCenter
    onHorizontalLabelAlignmentChanged: labelTitle.horizontalLabelAlignment = horizontalLabelAlignment
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
    // Set item width relative to width
    property double itemWidthScale: 0.95
    property int itemHeight: 50
    onItemHeightChanged: listItem.height = itemHeight
    property int itemWidth : listComponentBody.width * itemWidthScale
    onItemWidthChanged: listItem.width = itemWidth
    property color hoveredItemTextColor: "blue"
    onHoveredItemTextColorChanged: listItem.hoveredItemTextColor = hoveredItemTextColor
    property color itemBackgroundColor: "transparent"
    onItemBackgroundColorChanged: listItem.itemBackgroundColor = itemBackgroundColor

    property color itemImageBackgroundColor: "transparent"
    onItemImageBackgroundColorChanged: listItem.imageBackgroundColor = itemImageBackgroundColor

    property url itemImageUrl: ""
    onItemImageUrlChanged: listItem.logoUrl = itemImageUrl

    readonly property var currentIndexes: TournamentListViewScripts.currentIndexes()

    layer.enabled: true

    layer.effect: OpacityMask{
        maskSource: Item {
            width: listComponentBody.width
            height: listComponentBody.height

            Rectangle{
                anchors.fill: parent
                radius: listComponentBody.radius
            }
        }
    }
    Rectangle{
        id: backgroundRect
        anchors.fill: parent
        color: listComponentBody.backgroundColor
        opacity: 0.1
    }

    GridLayout
    {
        id: bodyLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom

        DefaultTitleComponent{
            id: labelTitle
            Layout.minimumHeight: 40
            Layout.fillWidth: true
            fontSize: listComponentBody.titleFontSize
            imageUrl: listComponentBody.titleImageUrl
            backgroundColor: listComponentBody.labelBackgroundColor
            backOpacity: listComponentBody.titleBackgroundOpacity
        }
        Rectangle{
            color: "transparent"
            height: 5
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
            delegate: MHViewDelegate{
                id: listItem
                logoUrl: listComponentBody.itemImageUrl
                onClicked: itemClicked(index)
                onCheckedChanged: itemSelected(index)
                title: tournamentTitle
                description: "Playercount: " + playersCount + " | Gamemode: " + gameMode;
                x: parent.width / 2 - listItem.width / 2
            }
        }
    }
}
