import QtQuick 2.12
import QtQuick.Layouts 1.12

GridLayout{
    id: gl

    width: 600
    height: 600

    columns: 10
    rows: 10

    columnSpacing: 0
    rowSpacing: 0

    signal complitedGame()
    property int value

    /*генерация новой игры*/
    function newGame(){
        var newGameConfigs = helper.newGame()
        for(var i = 0; i < newGameConfigs.length; i++)
            bricks.itemAt(i).config = newGameConfigs[i]
    }

    /*поиск всех соединённых клеток*/
    function light(){
        var brickConfigs = []
        for(var i = 0; i < bricks.count; i++)
            brickConfigs.push(bricks.itemAt(i).config)

        var brickLights = helper.light(brickConfigs)
        for(var j = 0; j < brickLights.length; j++)
            bricks.itemAt(j).light = brickLights[j]

    }

    /*подсчёт количества зажжённых клеток*/
    function lightsCount(){
        var brickLights = []
        var value = 0
        for(var k = 0; k < bricks.count; k++)
            brickLights.push(bricks.itemAt(k).light)

        for(var l = 0; l< brickLights.length; l++)
            if(brickLights[l])
                value++

        if(value===100){
            complitedGame()
        }
    }

    /*множим клетки со свойствами,описанными в Brick.qml*/
    Repeater {
        id: bricks
        model: 100

        Brick{
            /*при повороте одной клетки ,пересчитываем связанные клетки*/
            onRotated: gl.light()
        }
    }

    Component.onCompleted: {
       gl.newGame()
       gl.light()
    }
}
