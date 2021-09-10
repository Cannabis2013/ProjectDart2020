import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13

import "playerListViewScripts.js" as PLVScripts

Rectangle{
    id: listComponentBody
    color: "transparent"
    clip: true
    signal itemClicked(int index)
    signal itemSelected(int index)
    signal requestUpdate
    signal unSelectAll()
    onUnSelectAll: PLVScripts.unSelectAll()
    signal addItem(var item)
    onAddItem: PLVScripts.addItemModel(item)
    signal removeItems(var indexes)
    onRemoveItems: PLVScripts.removeItemModels(indexes)
    // Properties
    property string componentTitle: "Title"
    onComponentTitleChanged: labelTitle.text = componentTitle
    function clear(){
        listModel.clear();
    }
    readonly property var currentIndexes: PLVScripts.currentIndexes()

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
        color: "gray"
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
            imageUrl: listComponentBody.titleImageUrl
            backgroundColor: "lightgray"
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
            delegate: MHViewDelegate {
                id: listItem
                onClicked: itemClicked(index)
                onCheckedChanged: itemSelected(index)
                title: username
                description: "Mail: " + mail
            }
        }
    }
}
