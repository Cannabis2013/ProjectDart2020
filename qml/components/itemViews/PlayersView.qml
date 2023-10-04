import QtQuick 2.15
import "../../components/buttons"

Flickable {
        clip: true

        readonly property var playerNames: {
                let names = []
                for (var i = 0; i < playersModel.count; i++) {
                        const name = playersModel.get(i)
                        names.push(name.name)
                }
                return names
        }

        signal appendName(string name)
        onAppendName: playersModel.append({
                                                  "name": name
                                          })

        boundsBehavior: Flickable.StopAtBounds
        contentHeight: playersModel.count * 70 - 6
        contentWidth: 256

        ListView {
                id: listView
                anchors.fill: parent
                spacing: 6
                delegate: PlayerNameDelegate {
                        id: viewDelegate
                }
                model: ListModel {
                        id: playersModel
                }
        }
}
