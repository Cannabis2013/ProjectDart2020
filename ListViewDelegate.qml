import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13
Rectangle {
    id: body
    clip: true
    color: "transparent"

    MouseArea{
        focus: true
        anchors.fill: parent
        hoverEnabled: true
        onHoveredChanged: {
            if(containsMouse && body.state !== "checked")
                body.state = "hovered";
            else
                body.state = isCheckable && checked ? "checked" : "";
        }
        onPressAndHold: {
            if(noDelayPressSelect || !isCheckable)
                return;
            if(containsPress && body.isCheckable && !checked)
            {
                body.state = "checked";
                checkMarkScaleAni.start();
            }
            else
                body.state = "";
        }
        onClicked: {
            if(!checked)
                body.clicked();
            if(!noDelayPressSelect)
                return;
            if(body.isCheckable && !checked)
            {
                body.state = "checked";
                checkMarkScaleAni.start();
            }
            else
                body.state = "";
        }
    }

    signal clicked

    property int roundedCorners: 0
    onRoundedCornersChanged: body.radius = roundedCorners

    property bool noDelayPressSelect: false

    property bool isCheckable: false
    property bool checked: false

    property color selectedColor: backgroundRect.color
    property color selectedTextColor: label.color

    property double selectedSizeScale: 0.98

    property string title: ""
    onTitleChanged: labelTitle.text = title

    property color labelBackgroundColor: "lightgray"
    onLabelBackgroundColorChanged: labelTitle.color = labelBackgroundColor

    property color descriptionBackgroundColor : "transparent"
    onDescriptionBackgroundColorChanged : labelDescription.color = descriptionBackgroundColor

    property string description: ""
    onDescriptionChanged: labelDescription.text = description

    property int titleFontSize: 10
    onTitleFontSizeChanged: labelTitle.fontSize = titleFontSize

    property int descriptionFontSize: 8
    onDescriptionFontSizeChanged: labelDescription.fontSize = descriptionFontSize

    property color titleFontColor: "black"
    onTitleFontColorChanged: labelTitle.fontColor = titleFontColor
    property color descriptionFontColor: "white"
    onDescriptionFontColorChanged: labelDescription.fontColor = descriptionFontColor

    property color imageBackgroundColor: "transparent"
    onImageBackgroundColorChanged: imageRect.color = imageBackgroundColor
    property color backgroundColor: "transparent"
    onBackgroundColorChanged: backgroundRect = backgroundColor
    property double backgroundOpacitity: 0.3
    onBackgroundOpacitityChanged: backgroundRect.opacity = backgroundOpacitity

    property bool enableHover: true

    property double hoveredSizeScale: 0.90

    property color hoveredColor: "transparent"
    property color hoveredTitleColor: titleFontColor
    property color hoveredDescriptionColor: descriptionFontColor

    property url logoUrl: ""
    onLogoUrlChanged: imageRect.source = logoUrl
    border.color: "white"
    border.width: 1

    Rectangle{
        id: backgroundRect
        anchors.fill: parent

        color: body.backgroundColor
        opacity: body.backgroundOpacitity
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
            height: 9
            Layout.fillWidth: true
            color: "transparent"
        }

        Rectangle{
            id: leftPadding

            Layout.row: 1
            Layout.column: 0
            Layout.fillHeight: true
            width: 9
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
                color: body.labelBackgroundColor
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
                color: body.descriptionBackgroundColor
            }
        }
        Rectangle{
            id: bottomPadding

            Layout.row: 2
            Layout.column: 0
            Layout.columnSpan: 3
            height: 9
            Layout.fillWidth: true
            color: "transparent"
        }
        Rectangle{
            id: rightPadding

            Layout.row: 1
            Layout.column: 2
            Layout.fillHeight: true
            width: 9
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
            }
            PropertyChanges {
                target: backgroundRect
                color: selectedColor
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
            PropertyChanges {
                target: backgroundRect
                color: hoveredColor
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
