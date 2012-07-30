import com.nokia.meego 1.1
import QtQuick 1.1
import org.nemomobile.accountsui 1.0

Page {
    property Account account

    PageHeader {
        id: header
        text: account.id
    }

    Item {
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: UiConstants.DefaultMargin

        Label {
            anchors.fill: parent
            text: account.details
        }
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "icon-m-toolbar-back"
            onClicked: {
                pageStack.pop()
            }
        }
        ToolIcon {
            iconId: "icon-m-toolbar-refresh"
            onClicked: {
                account.refresh()
            }
        }
    }

}
