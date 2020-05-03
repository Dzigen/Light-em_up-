import QtQuick 2.12
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

RowLayout{
    id:rlt

    /*отправление сигнала на выполнение функций из Gameplay.qml*/
    signal newGame()
    signal quitApp()
    signal light()
    signal lightsCount()


    /*свойства для работы таймера*/
    property var locale: Qt.locale()
    property string dateTimeString: "02:01"
    property string dateTimeStringEnd: "00:00"

    property date startTime
    property date specTime

    /*флаг зажжения всех клеток*/
    property bool lightsOn: false

    function complitedGame(){
        lightsOn=true
    }

    Button{
        id: newGameButton

        text: "New Game"
        onClicked:{
            newGame()
            light()
            lightsOn=false
            rlt.startTime = new Date()
            rlt.specTime = Date.fromLocaleString(locale, dateTimeString, "mm:ss")
        }
   }

    TextField{
        id: timeField
        Layout.fillHeight: true
        Layout.fillWidth: true

        verticalAlignment: Text.AlignHCenter
        horizontalAlignment: Text.AlignHCenter
    }


    Button{
        id: quitButton

        text: "Quit"
        onClicked: quitApp()
    }

    Timer {
        id:clock
        interval: 10
        repeat: true
        running: true
        onTriggered: {
            var currntTime = new Date()
            var deltaTime = new Date(currntTime-startTime)
            var bacwardTime = new Date(specTime-deltaTime)

            /*если игрок зажёг все клетки раньше времени,то выводим диалоговое окно*/
            lightsCount()
            if(rlt.lightsOn){
                clock.stop()
                messageDialog.text="You WON.Wanna play again?"
                messageDialog.visible = true

              /*иначе,проверяем: не закончилось ли заданное время на игру*/
            }else if(Qt.formatTime(bacwardTime, "mm:ss") == dateTimeStringEnd){
                clock.stop()

                messageDialog.text="You LOSS.Wanna try again?"
                messageDialog.visible = true
            }

            timeField.text=Qt.formatTime(bacwardTime, "mm:ss")
        }
     }

    MessageDialog {
        id: messageDialog
        title: "Game over"
        standardButtons:StandardButton.Yes|StandardButton.No

        /*при нажатии на кнопку стартуем игру заного*/
        onYes: {
            newGame()
            light()
            lightsOn=false
            clock.start()
            rlt.startTime = new Date()
            rlt.specTime = Date.fromLocaleString(locale, dateTimeString, "mm:ss")
        }

        /*при нажатии на кнопку выходим из игры*/
        onNo: quitApp()
    }

    /*горячие клавиши*/

    Shortcut{
        context: Qt.ApplicationShortcut
        sequences: ["Ctrl+N"]
        onActivated: {
            newGame()
            light()
            lightsOn=false
            rlt.startTime =  new Date()
            rlt.specTime = Date.fromLocaleString(locale, dateTimeString, "mm:ss")
        }
    }

    Shortcut{
        context: Qt.ApplicationShortcut
        sequences: [StandardKey.Close,"Ctrl+Q"]
        onActivated: quitApp()
    } 

    Component.onCompleted:{
        rlt.startTime = new Date()
        rlt.dateTimeString="02:01"
        rlt.specTime = Date.fromLocaleString(locale, dateTimeString, "mm:ss")
        rlt.dateTimeStringEnd= "00:00"
        clock.start()
    }
}
