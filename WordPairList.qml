import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import wordpairmodel 1.0

ListView {
    id: wordpairlist
    anchors.fill: parent
    model: WordPairModel{}
    delegate: TwoEditFieldsDelegate {}

    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AlwaysOn
    }
}
