import com.nokia.meego 1.1
import QtQuick 1.1
import org.nemomobile.accountsui 1.0

PageStackWindow {
    id: window
    initialPage: Page {
        id: page
        PageHeader {
            id: header
            text: "Accounts"
        }

        ListView {
            clip: true
            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            model: AccountsModel {
                id: accountmodel
            }

            delegate: Item {
                height: 64
                width: parent.width
                Label {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: UiConstants.DefaultMargin
                    text: model.account.id
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("AccountPage.qml"), { account: model.account})
                    }
                }
            }
        }

        tools: ToolBarLayout {
            ToolIcon {
                iconId: "icon-m-common-add"
                onClicked: {
                    editor.open()
                }
            }
        }
    }

    AccountEditSheet {
        id: editor

        onAccepted: {
            if (!accountmodel.createAccount(protocol, userName, password)) {
                errorTitle.text = "Account creation failed"
                subtext.text = accountmodel.errorString()
                error.open()
            }
        }
    }

    Dialog {
        id: error
        title: Label {
            id: errorTitle
            color: "white"
        }

        content: Label {
            id: subtext
            color: "white"
            width: parent.width
        }
    }
}
