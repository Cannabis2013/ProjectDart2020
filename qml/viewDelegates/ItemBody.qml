import QtQuick 2.15
import QtQuick.Layouts 1.3

import "../geometry"
import "../viewObjects"
import "listViewDelegateScripts.js" as LVDScripts

BoxedRect {
        id: delegateBody
        property string description: ""
        onDescriptionChanged: labelDescription.text = description
        property url imageUrl: ""
        onImageUrlChanged: imageRect.source = imageUrl
        property string title: ""
        onTitleChanged: labelTitle.text = title
        contentRect: GridLayout {
                Layout.row: 1
                Layout.column: 1
                flow: GridLayout.LeftToRight
                columnSpacing: 0
                rowSpacing: 0
                Layout.fillHeight: true
                Layout.fillWidth: true
                rows: 2
                columns: 2
                DecoratedItem {
                        id: imageRect
                        Layout.fillHeight: true
                        Layout.preferredWidth: height
                        Layout.rowSpan: 2
                        color: "transparent"
                        source: delegateBody.imageUrl
                }
                MyLabel {
                        id: labelTitle
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        textLeftMargin: 9
                        text: delegateBody.title
                        fontSize: 16
                        verticalTextAlignment: Qt.AlignVCenter
                        horizontalTextAlignment: Qt.AlignLeft
                        fontColor: "white"
                }
                MyLabel {
                        id: labelDescription
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        textLeftMargin: 9
                        text: delegateBody.description
                        fontSize: 8
                        fontColor: "white"
                        verticalTextAlignment: Qt.AlignVCenter
                        horizontalTextAlignment: Qt.AlignLeft
                }
        }
}
