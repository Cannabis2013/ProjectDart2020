import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3

Item {
    id: headerRect

    focus: true

    property string buttonText: "Back"
    onButtonTextChanged: pageButton.text = buttonText

    property string pageTitle: ""
    onPageTitleChanged: pageLabel.text = pageTitle
    
    height: 48
    
    Button {
        id: pageButton
        
        anchors.margins: 8
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        
        font.pointSize: 16
        font.weight: Font.Bold
        
        text: buttonText
        
        height: 40
        
        onClicked: backClicked()
    }
    
    Text {
        id: pageLabel
        
        height: 32
        
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: pageButton.right
        anchors.leftMargin: 8
        anchors.right: parent.right
        
        font.pointSize: 16
        
        color: "white"
        
        verticalAlignment: Text.AlignVCenter
    }
}
