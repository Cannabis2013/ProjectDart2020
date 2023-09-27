import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import "../"
import "../../viewObjects"
import "../../viewDelegates"
import "playerListViewScripts.js" as PLVScripts

ItemListView {
        id: listComponentBody

        radius: 10

        onUnSelectAll: PLVScripts.unSelectAll()
        onAddItem: PLVScripts.addItemModel(item)
        onRemoveItems: PLVScripts.removeItemModels(indexes)
        onClear: listModel.clear()
        onComponentTitleChanged: labelTitle.text = componentTitle

        property string componentTitle: "Players"

        function selectedIndexes() {
                return PLVScripts.currentIndexes()
        }

        GridLayout {
                id: bodyLayout
                anchors.fill: parent
                flow: GridLayout.TopToBottom

                TitleItem {
                        id: labelTitle
                        Layout.minimumHeight: 40
                        Layout.fillWidth: true
                }
                Rectangle {
                        color: "transparent"
                        height: 5
                }
                ListView {
                        id: listView
                        clip: true
                        spacing: 5
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        boundsMovement: ListView.StopAtBounds
                        add: Transition {
                                NumberAnimation {
                                        property: "scale"
                                        from: 0
                                        to: 1
                                        duration: 200
                                }
                        }
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
