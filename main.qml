import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12

Window{
    id: w

    visible: true

    minimumWidth: 600
    maximumWidth: 600
    width: 600

    maximumHeight: cl.height
    minimumHeight: cl.height
    height: cl.height

    title: qsTr("Light`em Up!")

    ColumnLayout{
        id: cl

        anchors.centerIn: w.contentItem
        spacing: 2

        Gameplay{
            id: gameplay

            onComplitedGame: toolbar.complitedGame()
        }

        Toolbar{
            id: toolbar

            onLight: gameplay.light()
            onLightsCount: gameplay.lightsCount()
            onNewGame: gameplay.newGame()
            onQuitApp: Qt.quit()
        }
    }
}
