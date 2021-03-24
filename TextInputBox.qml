import QtQuick 2.15
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

UserInputContent
{
    id: body
    color: "white"
    radius: 0
    /*
      Properties
      */
    property color fontColor: "black"
    onFontColorChanged: titleEdit.color = fontColor
    property bool isNumeric: false
    property bool interactive: true
    onInteractiveChanged: titleEdit.readOnly = interactive
    /*
      Event handling
      */
    onFontSizeChanged: titleEdit.font.pointSize = fontSize
    onSetValue: titleEdit.text = value
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
        readOnly: !body.interactive
        Keys.onPressed: {
            if(event.key === Qt.Key_Enter ||event.key === Qt.Key_Return)
            {
                enterPressed();
            }
        }
        anchors.fill: parent
        font.pointSize: fontSize
        wrapMode: TextEdit.NoWrap
        verticalAlignment: TextEdit.AlignVCenter
        horizontalAlignment: TextEdit.AlignHCenter
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
            if(isNumeric && isNaN(txt))
                clear();
            body.currentValue = text;
            body.valueChanged(text)
        }
    }
}
