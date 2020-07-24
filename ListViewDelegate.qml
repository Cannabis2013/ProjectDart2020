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
            if(containsMouse && body.state !== "Checked")
                body.state = "Hovered";
            else
                body.state = "";
        }
        onPressedChanged: {
            if(containsPress)
                body.state = "Pressed"
            else
                body.state = isCheckable && checked ? "Checked" : "";;
        }
        onClicked: body.clicked()
    }

    signal clicked

    property int roundedCorners: 0
    onRoundedCornersChanged: body.radius = roundedCorners

    property bool isCheckable: false
    property bool checked: false

    property color selectedColor: body.color
    property color selectedTextColor: label.color

    property string text: ""
    onTextChanged: label.text = text

    property int fontSize: 12
    onFontSizeChanged: label.fontSize = fontSize

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
        flow: GridLayout.LeftToRight


        Rectangle
        {
            id: imageRect
            clip: true
            Layout.fillHeight: true
            Layout.preferredWidth: body.height

            color: "gray"
            Image
            {
                id: imageDecorator
                anchors.fill: parent
                source: body.imageUrl
            }
        }

        MyLabel{
            id: label
            Layout.fillHeight: true
            Layout.fillWidth: true
            textLeftMargin: 9
            text: body.text
            fontSize: body.fontSize
            verticalTextAlignment: Qt.AlignVCenter
            horizontalTextAlignment: Qt.AlignLeft
            fontColor: body.textColor
        }
    }
    states: [
        State {
            name: "Checked"
            PropertyChanges {
                target: body
                scale: 0.85
                color: selectedColor
            }
        },
        State {
            name: "Hovered"
            PropertyChanges {
                target: body
                color: hoveredColor
            }
            PropertyChanges {
                target: label
                fontColor: body.hoveredTextColor
            }
        },
        State {
            name: "Pressed"
            PropertyChanges {
                target: body
                scale: 0.80
            }
        }
    ]
}
