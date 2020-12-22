import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

GridLayout{
    id: body
    flow: GridLayout.TopToBottom

    signal startButtonClicked
    signal pressAndHoldClicked

    signal enablePressAndHold(bool enable)
    onEnablePressAndHold: startButton.enablePressAndHold = enable

    property string startButtonText: "value"
    onStartButtonTextChanged: startButton.text = startButtonText
    property bool startButtonEnabled: false
    onStartButtonEnabledChanged: startButton.enabled = startButtonEnabled
    
    MyLabel{
        Layout.alignment: Qt.AlignTop
        
        text: qsTr("Hold for restart")
        fontColor: "white"
        width: 64
        Layout.fillHeight: true
        wrapMode: Text.WrapAnywhere
        verticalTextAlignment: Text.AlignBottom
        horizontalTextAlignment: Text.AlignHCenter
    }
    
    PushButton{
        id: startButton
        text: body.startButtonText
        textColor: ThemeContext.navStartButtonTextColor
        backgroundColor: ThemeContext.navStartButtonBackgroundColor
        hoveredColor: ThemeContext.navStartButtonHoveredBackgroundColor
        buttonRadius: 6
        fontSize: 12
        width: 64
        height: 24
        enablePressAndHold: body.startButtonEnabled
        
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        onClicked: body.startButtonClicked()
        onPressAndHoldClicked: body.pressAndHoldClicked()
        enabled: body.startButtonEnabled
    }
    Rectangle{
        Layout.fillHeight: true
    }
}
