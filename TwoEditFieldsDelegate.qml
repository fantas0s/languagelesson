import QtQuick 2.0
import QtQuick.Controls 2.2
import worddatabase 1.0

Pane {
    id: delegateRoot
    width: parent.width
    height: localWordEdit.height + 10

    TextField {
        id: localWordEdit
        width: (parent.width / 2) - 10
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        text: localText
        onEditingFinished: {
            WordDatabase.setWord(index, WordDatabase.LocalWord, text);
        }
    }
    TextField {
        id: foreignWordEdit
        width: (parent.width / 2) - 10
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        text: foreignText
        onEditingFinished: {
            WordDatabase.setWord(index, WordDatabase.ForeignWord, text);
        }
    }
}
