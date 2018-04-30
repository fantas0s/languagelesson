import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    //visibility: Window.FullScreen

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Pane {
            id: pane

            WordPairList {
                id: wordpairlist
                anchors.fill: parent
            }
        }
    }

    property int fps:0
    property int fpsCounter:0
}
