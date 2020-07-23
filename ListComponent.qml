import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13

Rectangle{
    id: listComponentBody

    color: "transparent"

    clip: true

    property bool allowCheckState: false
    onAllowCheckStateChanged: listItem.allowCheckState = allowCheckState

    property bool allowMultipleSelections: false

    property string componentTitle: "Title"
    onComponentTitleChanged: labelTitle.text = componentTitle

    property color itemTextColor: "black"
    onItemTextColorChanged: listItem.itemTextColor = itemTextColor

    property int itemFontSize: 10
    onItemFontSizeChanged: listItem.itemFontSize = itemFontSize

    property color itemSelectedBackgroundColor: "white"
    onItemSelectedBackgroundColorChanged: listItem.itemSelectedBackgroundColor = itemSelectedBackgroundColor

    property color itemSelectedtextColor: "black"
    onItemSelectedtextColorChanged: listItem.itemSelectedtextColor = itemSelectedtextColor

    property int itemHeight: 50
    onItemHeightChanged: listItem.itemHeight = itemHeight

    property int itemWidth : listComponentBody.width
    onItemWidthChanged: listItem.itemWidth = itemWidth

    property color itemHoveredColor: "transparent"
    onItemHoveredColorChanged: listItem.itemHoveredColor = itemHoveredColor

    property color hoveredItemTextColor: "blue"
    onHoveredItemTextColorChanged: listItem.hoveredItemTextColor = hoveredItemTextColor

    property color itemBackgroundColor: "transparent"
    onItemBackgroundColorChanged: listItem.itemBackgroundColor = itemBackgroundColor

    readonly property var currentlySelectedIndex: function(){return indexContainer.getCurrentlySelectedIndex;}
    readonly property var currentlySelectedIndexes: function(){return indexContainer.getCurrentlySelectedIndexes;}

    QtObject{
        id: indexContainer
        property int currentlySelectedIndex : -1
        property var currentlySelectedIndexes: []
    }

    signal itemSelected(int index)

    function clear(){
        listModel.clear();
    }

    function buttonSelected(text){
        var cIndex = -1;
        var cIndexes = [];
        var j = 0;
        for(var i = 0;i < listView.count;i++)
        {
            var item = listView.itemAtIndex(i);
            var txt = item.text;
            if(allowMultipleSelections){
                if(item.buttonBody.state === "checked")
                    cIndexes[j++] = i;
            }
            else{
                if(item.buttonBody.state === "checked" && txt !== text)
                    item.buttonBody.state = "";
                if(txt === text && item.buttonBody.state === "checked")
                {
                    cIndex = i;
                    itemSelected(cIndex);
                }
            }
        }
        indexContainer.currentlySelectedIndex = cIndex;
        indexContainer.currentlySelectedIndexes = cIndexes;
    }

    function addPlayerItem(userName)
    {
        var model = {"type" : "player","Username" : userName};
        listModel.append(model);
    }

    function addTournamentItem(tournamentTitle,
                               tournamentThrowsCount,
                               tournamentKeyPoint,
                               tournamentPlayersCount)
    {
        var model = {"type" : "tournament",
            "tournamentTitle" : tournamentTitle,
            "Throws" : tournamentThrowsCount,
            "KeyPoint" : tournamentKeyPoint,
            "playersCount" : tournamentPlayersCount};

        listModel.append(model);
    }

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
            spacing: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: ListModel {
                id: listModel
            }

            delegate: PushButton{
                id: listItem

                clip: true

                fontSize: itemFontSize

                isCheckable: allowCheckState
                onEmitCheckState: buttonSelected(text);

                hoveredColor: listComponentBody.itemHoveredColor
                hoveredTextColor: listComponentBody.hoveredItemTextColor

                checkedBackgroundColor: listComponentBody.itemSelectedBackgroundColor
                checkedTextColor: listComponentBody.itemSelectedtextColor

                height: listComponentBody.itemHeight
                width: listComponentBody.itemWidth

                backgroundColor: listComponentBody.itemBackgroundColor
                textColor: listComponentBody.itemTextColor

                text: {
                    if(type == "player")
                        return Username;
                    else if(type == "tournament")
                    {
                        return tournamentTitle + "\n" + " Throws: " + Throws + "\n" +
                                "Keypoint: " + KeyPoint + " Playercount: " + playersCount;
                    }
                }
                x: parent.width / 2 - width / 2
            }
        }
    }
}
