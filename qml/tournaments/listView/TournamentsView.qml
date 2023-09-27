import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import "tournamentsViewScripts.js" as TLVScripts
import "../../viewDelegates"
import "../../viewObjects"

ItemListView {
        id: listComponentBody

        radius: 10

        property bool enableCheck: true
        property bool instantCheck: true
        property string componentTitle: "Tournaments"

        function selectedIndexes() {
                return TLVScripts.currentIndexes()
        }

        onAddItem: TLVScripts.addItemModel(item)
        onRemoveItems: TLVScripts.removeItemModels(indexes)
        onUnSelectAll: TLVScripts.unSelectAll()
        onClear: listModel.clear()
        onComponentTitleChanged: labelTitle.text = componentTitle

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

                        delegate: TournamentViewDelegate {
                                id: listItem
                                noDelayPressSelect: listComponentBody.instantCheck
                                onClicked: itemClicked(index)
                                onCheckedChanged: itemSelected(index)
                                title: tournamentTitle
                                description: "Playercount: " + playersCount + " | Gamemode: " + gameMode
                                x: parent.width / 2 - listItem.width / 2
                                isCheckable: listComponentBody.enableCheck
                        }
                }
        }
}
