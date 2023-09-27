import QtQuick 2.15
import QtQuick.Layouts 1.3

import "../"
import "../viewObjects"
import "listViewDelegateScripts.js" as LVDScripts

ViewDelegate {
        id: body
        onHoverEvent: LVDScripts.onHover(sustained)
        onPressAndHoldEvent: LVDScripts.onPressAndHold()
        onClickEvent: LVDScripts.onClick()
        signal clicked
        onTitleChanged: delegateBody.title = title
        onDescriptionChanged: delegateBody.description = description
        onLogoUrlChanged: delegateBody.imageUrl = logoUrl
        ItemBody {
                id: delegateBody
                anchors.fill: parent
                padding: 4
        }
        DecoratedItem {
                id: checkMark
                source: "qrc:/pictures/Ressources/checkmark.png"
                anchors.right: parent.right
                visible: false
                height: 25
                width: 25
        }
        states: [
                State {
                        name: ""
                        PropertyChanges {
                                target: body
                                scale: 1
                        }
                },
                State {
                        name: "checked"
                        PropertyChanges {
                                target: body
                                scale: body.selectedSizeScale
                                checked: true
                                backgroundColor: selectedColor
                        }
                        PropertyChanges {
                                target: checkMark
                                visible: true
                        }
                },
                State {
                        name: "hovered"
                        PropertyChanges {
                                target: body
                                scale: body.hoveredSizeScale
                        }
                },
                State {
                        name: "pressed"
                        PropertyChanges {
                                target: body
                                scale: 0.90
                                checked: checked ? false : true
                        }
                }
        ]
}
