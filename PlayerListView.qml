import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13

import "playerListViewScripts.js" as PLVScripts

ItemListView{
    id: listComponentBody
    onUnSelectAll: PLVScripts.unSelectAll()
    onAddItem: PLVScripts.addItemModel(item)
    onRemoveItems: PLVScripts.removeItemModels(indexes)
    onClear: listModel.clear()
    // Properties
    property string componentTitle: "Title"
    onComponentTitleChanged: labelTitle.text = componentTitle
    readonly property var currentIndexes: PLVScripts.currentIndexes()
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
            delegate: PlayerViewDelegate {
                id: listItem
                onClicked: itemClicked(index)
                onCheckedChanged: itemSelected(index)
                title: username
                description: "Mail: " + mail
            }
        }
    }
}
