import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0


Rectangle
{
    id: myTextEditBody

    clip: true

    property int fontSize: 24
    onFontSizeChanged: titleEdit.font.pointSize = fontSize

    property color fontColor: "black"
    onFontColorChanged: titleEdit.color = fontColor

    property bool numericOnly: false

    property string currentText: {

        var text = titleEdit.text;

        if(!isNan(text))
            return titleEdit.text
        else
            return ""

    }

    TextEdit{
        id: titleEdit

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
            if(numericOnly)
            {
                var txt = text;

                if(isNaN(txt))
                    clear();
            }
        }
    }
}
