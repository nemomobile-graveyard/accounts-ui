import com.nokia.meego 1.1
import QtQuick 1.1

Sheet {
    acceptButtonText: "Save"
    rejectButtonText: "Cancel"
    property alias userName: user.text
    property alias password: pass.text
    property alias protocol: protocolButton.text

    content: Flickable {
        id: flickable
        anchors.fill: parent
        anchors.margins: UiConstants.DefaultMargin
        contentHeight: childrenRect.height
        Column {
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: UiConstants.DefaultMargin

            Button {
                id: protocolButton
                text: "XMPP"
                width: parent.width

                onClicked: {
                    protocolDialog.open()
                }
            }
            TextField {
                id: user
                placeholderText: "Username"
                width: parent.width
            }
            TextField {
                id: pass
                placeholderText: "Password"
                width: parent.width
            }
        }
    }

    SelectionDialog {
        id: protocolDialog
        titleText: "Account Protocol"
        model: ListModel {
            ListElement { name: "XMPP" }
            ListElement { name: "SIP" }
        }

        onAccepted: {
            protocolButton.text = model.get(selectedIndex).name
        }
    }
}
