import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13
Rectangle {
    id: body
    clip: true
    color: backgroundColor

    layer.enabled: true
    layer.effect: OpacityMask{
        maskSource: Item {
            width: body.width
            height: body.height
            Rectangle{
                anchors.fill: parent
                radius: body.radius
            }
        }
    }

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
        onPressedChanged:
        {
            if(containsPress && !body.pressAndHoldEnabled)
                body.state = "pressed";
            else if(body.state !== "checked" && !body.pressAndHoldEnabled)
                body.state = "";
        }

        onPressAndHold: {
            var a = body.pressAndHoldEnabled;
            var b = body.isCheckable;
            if(containsPress && (body.pressAndHoldEnabled || body.isCheckable) && !checked)
                body.state = "checked"
            else
                body.state = "";
        }

        onClicked: body.clicked()
    }

    signal clicked

    property int roundedCorners: 0
    onRoundedCornersChanged: body.radius = roundedCorners

    property bool isCheckable: false
    property bool checked: false

    property bool pressAndHoldEnabled: false

    property color selectedColor: body.color
    property color selectedTextColor: label.color

    property string title: ""
    onTitleChanged: labelTitle.text = title

    property string description: ""
    onDescriptionChanged: labelDescription.text = description

    property int titleFontSize: 12
    onTitleFontSizeChanged: labelTitle.fontSize = titleFontSize

    property int descriptionFontSize: 10
    onDescriptionFontSizeChanged: labelDescription.fontSize = descriptionFontSize

    property color textColor: label.fontColor
    onTextColorChanged: label.fontColor = textColor

    property color backgroundColor: "transparent"
    onBackgroundColorChanged: body.color = backgroundColor

    property color hoveredColor: "transparent"
    property color hoveredTextColor: label.color

    property url imageUrl: ""
    onImageUrlChanged: imageDecorator.source = imageUrl

    GridLayout
    {
        id: bodyLayout
        anchors.fill: parent
        rows: 2
        columns: 2
        flow: GridLayout.LeftToRight
        columnSpacing: 0
        DecoratedItem {
            id: imageRect
            Layout.fillHeight: true
            Layout.preferredWidth: body.height
            Layout.rowSpan: 2
            color: "gray"
            source: body.imageUrl
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
            fontColor: body.textColor
            color: "lightgray"
        }
        MyLabel{
            id: labelDescription
            Layout.fillHeight: true
            Layout.fillWidth: true
            textLeftMargin: 9
            text: body.description
            fontSize: body.descriptionFontSize
            verticalTextAlignment: Qt.AlignVCenter
            horizontalTextAlignment: Qt.AlignLeft
            fontColor: body.textColor
        }

    }

    DecoratedItem{
        id:checkMark
        source: "qrc:/pictures/Ressources/checkmark.png"
        anchors.right: parent.right
        visible: false
        height: parent.height
        width: height
    }

    Rectangle
    {
        id: maskRect
        anchors.fill: parent
        color: "blue"
        opacity: 0.2
        visible: false
    }

    states: [
        State {
            name: "checked"
            PropertyChanges {
                target: body
                scale: 0.95
                color: selectedColor
                checked: true
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
                color: hoveredColor
            }
            PropertyChanges {
                target: labelTitle
                fontColor: body.hoveredTextColor
            }
            PropertyChanges {
                target: labelDescription
                fontColor: body.hoveredTextColor
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
