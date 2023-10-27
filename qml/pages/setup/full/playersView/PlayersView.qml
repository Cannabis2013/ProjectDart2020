import QtQuick 2.15

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

        QtObject {
                id: playerNameContainer
                property var names: []
        }

        signal appendName(string name)
        onAppendName: name => {
                              const existingNames = playerNameContainer.names
                              for (var i = 0; i < existingNames.length; i++) {
                                      const n = existingNames[i]
                                      if (n === name) {
                                              return
                                      }
                              }
                              const obj = {
                                      "name": name
                              }
                              existingNames.push(obj.name)
                              playersModel.append(obj)
                      }

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
