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

    property color textColor: labelTitle.fontColor
    onTextColorChanged: {
        labelTitle.fontColor = textColor;
        labelDescription.fontColor = textColor;
    }

    property color backgroundColor: "transparent"
    onBackgroundColorChanged: body.color = backgroundColor

    property color hoveredColor: "transparent"
    property color hoveredTextColor: label.color

    property url logoUrl: ""
    onLogoUrlChanged: imageRect.source = logoUrl

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
                scale: 0.98
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
                scale:0.98
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
