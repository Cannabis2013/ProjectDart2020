import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3


import "tournamentListViewScripts.js" as TLVScripts

ItemListView{
    id: listComponentBody
    onAddItem: TLVScripts.addItemModel(item)
    onRemoveItems: TLVScripts.removeItemModels(indexes)
    onUnSelectAll: TLVScripts.unSelectAll()
    onClear: listModel.clear()
    // Item properties
    property bool enableCheck: true
    property bool instantCheck: true
    // Title properties
    property string componentTitle: "Title"
    onComponentTitleChanged: labelTitle.text = componentTitle
    // Get current indexes
    readonly property var currentIndexes: TLVScripts.currentIndexes()
    GridLayout
    {
        id: bodyLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom

        DefaultTitleComponent{
            id: labelTitle
            Layout.minimumHeight: 40
            Layout.fillWidth: true
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
            delegate: TournamentViewDelegate{

                id: listItem
                noDelayPressSelect: listComponentBody.instantCheck
                onClicked: itemClicked(index)
                onCheckedChanged: itemSelected(index)
                title: tournamentTitle
                description: "Playercount: " + playersCount + " | Gamemode: " + gameMode;
                x: parent.width / 2 - listItem.width / 2
                isCheckable: listComponentBody.enableCheck
            }
        }
    }
}