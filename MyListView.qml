import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

ListView
{
    id: listViewBody

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

    property int itemWidth : listViewBody.width
    onItemWidthChanged: listItem.width = itemWidth

    property color itemHoveredColor: "transparent"
    onItemHoveredColorChanged: listItem.hoveredColor = itemHoveredColor

    property color hoveredItemTextColor: "blue"
    onHoveredItemTextColorChanged: listItem.hoveredTextColor = hoveredItemTextColor

    property color itemBackgroundColor: "transparent"
    onItemBackgroundColorChanged: listItem.backgroundColor = itemBackgroundColor

    function getSelectedIndexes()
    {
        var indexes;
        var j = 0;
        for(var i = 0;i < count;i++)
        {
            var item = itemAtIndex(i);
            if(item.checked === true)
                indexes[j++] = i;
        }
        return indexes;
    }

    function getCurrentIndex(){
        var index = currentIndex;
        if(index === -1)
            throw "No object appears to be selected"
        return index;
    }

    function addPlayerItem(firstName, lastName, eMail, id = 0)
    {
        var model = {"type" : "player","firstName" : firstName,"lastName" : lastName, "email" : eMail, "uuid" : id};
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

        isCheckable: true

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
