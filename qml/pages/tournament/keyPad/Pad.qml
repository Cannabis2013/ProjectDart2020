import QtQuick 2.15

Rectangle {
        id: padRect
        clip: true

        signal clicked

        onEnabledChanged: padRect.opacity = enabled ? 1 : 0.2

        property string text: ""
        onTextChanged: buttonText.text = qsTr(text)
        property color backgroundColor: "grey"
        onBackgroundColorChanged: padRect.color = backgroundColor
        property color fontColor: "black"
        onFontColorChanged: buttonText.color = fontColor

        property int fontSize: 28
        onFontSizeChanged: buttonText.font.pointSize = fontSize

        MouseArea {
                anchors.fill: parent
                onClicked: padRect.clicked()
        }

        Text {
                id: buttonText
                anchors.fill: parent
                text: qsTr(padRect.text)
                color: fontColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: padRect.fontSize
        }
}
