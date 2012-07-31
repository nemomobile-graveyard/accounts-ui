import com.nokia.meego 1.1
import QtQuick 1.1
import org.nemomobile.accountsui 1.0

Page {
    property Account account

    Connections {
        target: account
        onAccountRemoved: {
            pageStack.pop()
        }
    }

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
        ToolIcon {
            iconId: "icon-m-toolbar-view-menu"
            onClicked: (accountMenu.status == DialogStatus.Closed) ? accountMenu.open() : accountMenu.close()
        }
    }


    Menu {
        id: accountMenu
        MenuLayout {
            MenuItem {
                text: "Enable"
                onClicked: account.enable()
            }

            MenuItem {
                text: "Disable"
                onClicked: account.disable()
            }

            MenuItem {
                text: "Request online"
                onClicked: account.goOnline()
            }

            MenuItem {
                text: "Request offline"
                onClicked: account.goOffline()
            }


            MenuItem {
                text: "Remove"
                onClicked: account.remove()
            }

        }
    }
}
