import QtQuick 2.15
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

UserInputContent
{
    id: body
    color: "white"
    radius: 20
    /*
      Properties
      */
    property color fontColor: "black"
    onFontColorChanged: titleEdit.color = fontColor
    property bool isNumeric: false
    /*
      Event handling
      */
    onFontSizeChanged: titleEdit.font.pointSize = fontSize
    /*
      UserInputContent interface
      */
    currentValue: {
        var text = titleEdit.text;
        if(isNumeric && text === "")
            return -1;
        return text;
    }

    TextEdit{
        id: titleEdit
        focus: true
        Keys.onPressed: {
            if(event.key === Qt.Key_Enter ||event.key === Qt.Key_Return)
            {
                enterPressed();
            }
        }
        anchors.fill: parent
        anchors.leftMargin: 20
        font.pointSize: fontSize
        wrapMode: TextEdit.NoWrap
        verticalAlignment: Qt.AlignVCenter
        color: fontColor
        onLineCountChanged: {
            var txt = text;
            var nTxt = txt.replace("\n","");
            clear();
            titleEdit.text = nTxt;
            cursorPosition = nTxt.length
        }
        onTextChanged: {
            var txt = text;
            if(isNumeric)
            {
                if(isNaN(txt))
                    clear();
            }
            body.currentValue = text;
            body.valueChanged(text)
        }
    }
}
