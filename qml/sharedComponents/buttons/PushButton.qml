import QtQuick 2.0
import QtQuick.Controls

Button {
        id: buttonRect

        property string buttonText: "Text"
        onButtonTextChanged: textRect.text = buttonText

        property int fontSize: 12
        onFontSizeChanged: textRect.font.pointSize = fontSize

        onEnabledChanged: textRect.visible = enabled

        Text {
                id: textRect
                anchors.fill: parent
                font.pointSize: buttonRect.fontSize
                text: buttonRect.text
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
        }
}
