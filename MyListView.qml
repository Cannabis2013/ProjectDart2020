import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3



ListView
{
    id: listViewBody

    clip: true

    QtObject{
        id: indexContainer
        property int currentlySelectedIndex : -1
        property var currentlySelectedIndexes: []
    }

    signal itemSelected(int index)

    spacing: 1

    property bool allowCheckState: false
    onAllowCheckStateChanged: listItem.isCheckable = allowCheckState

    property bool allowMultipleSelections: false

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

    property int itemWidth : listViewBody.width
    onItemWidthChanged: listItem.width = itemWidth

    property color itemHoveredColor: "transparent"
    onItemHoveredColorChanged: listItem.hoveredColor = itemHoveredColor

    property color hoveredItemTextColor: "blue"
    onHoveredItemTextColorChanged: listItem.hoveredTextColor = hoveredItemTextColor

    property color itemBackgroundColor: "transparent"
    onItemBackgroundColorChanged: listItem.backgroundColor = itemBackgroundColor

    readonly property int getCurrentlySelectedIndex: indexContainer.currentlySelectedIndex;
    readonly property var getCurrentlySelectedIndexes: indexContainer.currentlySelectedIndexes

    function clear(){
        listModel.clear();
    }

    function buttonSelected(text){
        var cIndex = -1;
        var cIndexes = [];
        var j = 0;
        for(var i = 0;i < count;i++)
        {
            var item = itemAtIndex(i);
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

    function addPlayerItem(firstName, lastName, eMail)
    {
        var model = {"type" : "player","firstName" : firstName,"lastName" : lastName, "email" : eMail};
        listModel.append(model);
    }

    function addTournamentItem(tournamentTitle,
                               tournamentMaxPlayers,
                               tournamentLegsCount,
                               tournamentKeyPoint,
                               tournamentPlayersCount)
    {
        var model = {"type" : "tournament",
            "tournamentTitle" : tournamentTitle,
            "maxPlayers" : tournamentMaxPlayers,
            "legsCount" : tournamentLegsCount,
            "keyPoint" : tournamentKeyPoint,
            "playersCount" : tournamentPlayersCount};

        listModel.append(model);
    }
    
    model: ListModel {
        id: listModel
    }
    
    delegate: PushButton{
        id: listItem

        clip: true

        fontSize: itemFontSize

        isCheckable: allowCheckState
        onEmitCheckState: buttonSelected(text);

        hoveredColor: listViewBody.itemHoveredColor
        hoveredTextColor: listViewBody.hoveredItemTextColor

        checkedBackgroundColor: listViewBody.itemSelectedBackgroundColor
        checkedTextColor: listViewBody.itemSelectedtextColor

        height: listViewBody.itemHeight
        width: listViewBody.itemWidth

        backgroundColor: listViewBody.itemBackgroundColor
        textColor: listViewBody.itemTextColor

        text: {
            if(type == "player")
                return "Full name: " + firstName + " " + lastName + "\n" +
                          "E-mail: " + email;
            else if(type == "tournament")
            {
                return tournamentTitle + "\n" +
                        "Max players: " + maxPlayers + " Legs: " + legsCount + "\n" +
                        "Keypoint: " + keyPoint + " Playercount: " + playersCount;
            }
        }
        x: parent.width / 2 - width / 2
    }
}
