import QtQuick 2.15
import QtQuick.Layouts 1.3
import "listViewDelegateScripts.js" as LVDScripts
ViewDelegate {
    id: body
    onHoverEvent: LVDScripts.onHover(sustained)
    onPressAndHoldEvent: LVDScripts.onPressAndHold()
    onClickEvent: LVDScripts.onClick()
    signal clicked
    onTitleChanged: labelTitle.text = title
    onLabelBackgroundColorChanged: labelTitle.color = labelBackgroundColor
    onDescriptionBackgroundColorChanged : labelDescription.color = descriptionBackgroundColor
    onDescriptionChanged: labelDescription.text = description
    onTitleFontSizeChanged: labelTitle.fontSize = titleFontSize
    onDescriptionFontSizeChanged: labelDescription.fontSize = descriptionFontSize
    onImageBackgroundColorChanged: imageRect.color = imageBackgroundColor
    onDescriptionFontColorChanged: labelDescription.fontColor = descriptionFontColor
    onTitleFontColorChanged: labelTitle.fontColor = titleFontColor
    onLogoUrlChanged: imageRect.source = logoUrl
    QtObject{
        id: defaultPadding
        property int value: 4
    }
    GridLayout{
        id: bodyLayout
        rows: 3
        columns: 3
        anchors.fill: parent
        Rectangle{
            id: upperPadding
            Layout.row: 0
            Layout.column: 0
            GridLayout.columnSpan: 3
            height: defaultPadding.value
            Layout.fillWidth: true
            color: "transparent"
        }
        Rectangle{
            id: leftPadding
            Layout.row: 1
            Layout.column: 0
            Layout.fillHeight: true
            width: defaultPadding.value
            color: "transparent"
        }
        GridLayout
        {
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
                color: "transparent";
                source: body.logoUrl
            }
            MyLabel{
                id: labelTitle
                Layout.fillHeight: true
                Layout.fillWidth: true
                textLeftMargin: 9
                text: body.title
                fontSize: titleFontSize
                verticalTextAlignment: Qt.AlignVCenter
                horizontalTextAlignment: Qt.AlignLeft
                fontColor: body.titleFontColor
            }
            MyLabel{
                id: labelDescription
                Layout.fillHeight: true
                Layout.fillWidth: true
                textLeftMargin: 9
                text: body.description
                fontSize: body.descriptionFontSize
                fontColor: body.descriptionFontColor
                verticalTextAlignment: Qt.AlignVCenter
                horizontalTextAlignment: Qt.AlignLeft
            }
        }
        Rectangle{
            id: bottomPadding
            Layout.row: 2
            Layout.column: 0
            Layout.columnSpan: 3
            height: defaultPadding.value
            Layout.fillWidth: true
            color: "transparent"
        }
        Rectangle{
            id: rightPadding
            Layout.row: 1
            Layout.column: 2
            Layout.fillHeight: true
            width: defaultPadding.value
            color: "transparent"
        }
    }
    DecoratedItem{
        id:checkMark
        source: "qrc:/pictures/Ressources/checkmark.png"
        anchors.right: parent.right
        visible: false
        height: 25
        width: 25
        PropertyAnimation on scale{
            id: checkMarkScaleAni
            from: 0
            to: 1
            running: false
            duration: 125
            onFinished: checkMarkRotationAni.start()
        }
        PropertyAnimation on rotation {
            id: checkMarkRotationAni
            from: 360
            to:0
            running: false
            duration: 125
        }
    }
    states: [
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
                backgroundColor: hoveredColor
            }
            PropertyChanges {
                target: labelTitle
                fontColor: body.hoveredTitleColor
            }
            PropertyChanges {
                target: labelDescription
                fontColor: body.hoveredDescriptionColor
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
