import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle{
    id: defaultTitleComponentBody
    color: "transparent"
    property url imageUrl: ""
    onImageUrlChanged: {
        imageIcon.source = imageUrl;
        if(imageUrl !== "")
            imageIcon.width = 40;
        else
            imageIcon.width = 0;
    }

    property string text: ""
    onTextChanged: labelTitle.text = text
    property color backgroundColor: "transparent"
    onBackgroundColorChanged: backgroundRect.color = backgroundColor
    property double backOpacity: 1
    onBackOpacityChanged: backgroundRect.opacity = backOpacity
    property color fontColor: "black"
    onFontColorChanged: labelTitle.fontColor = fontColor
    property int horizontalLabelAlignment: Qt.AlignHCenter
    onHorizontalLabelAlignmentChanged: labelTitle.horizontalTextAlignment = horizontalLabelAlignment
    Rectangle{
        id: backgroundRect
        anchors.fill: parent
        color: defaultTitleComponentBody.backgroundColor
        opacity: defaultTitleComponentBody.backOpacity
    }

    GridLayout{
        flow: GridLayout.TopToBottom
        anchors.fill: parent
        Rectangle{
            id: upperSpacer
            color: "transparent"
            Layout.fillWidth: true
            height: 10
        }
        GridLayout{
            flow: GridLayout.LeftToRight
            Layout.fillWidth: true
            Layout.fillHeight: true
            Rectangle{
                id: leftSpacer
                Layout.fillHeight: true
                width: parent.width*(1-0.95)/2
                color: "transparent"
            }

            DecoratedItem{
                id: imageIcon
                Layout.fillHeight: true
                width: 0
                color: "transparent"
                source: defaultTitleComponentBody.imageUrl
            }
            LabelComponent {
                id: labelTitle
                Layout.fillWidth: true
                Layout.fillHeight: true
                fontSize: 24
                backgroundColor: "transparent"
                fontColor: defaultTitleComponentBody.fontColor
                text: defaultTitleComponentBody.text
                horizontalTextAlignment: defaultTitleComponentBody.horizontalLabelAlignment
            }
            DecoratedItem{
                Layout.fillHeight: true
                width: 0
                color: "transparent"
            }
            Rectangle{
                id: rightSpacer
                Layout.fillHeight: true
                width: 10
                color: "transparent"
            }
        }
        Rectangle{
            id: lowerSpacer
            color: "transparent"
            Layout.fillWidth: true
            height: 10
        }
    }
}
