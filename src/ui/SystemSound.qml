import QtMultimedia 6.0
import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Dialogs 6.2
import QtQuick.Layouts 2.15

import org.kde.kirigami 2.7 as Kirigami

Item {
  id: root
  height: row.implicitHeight

  property string text: ""
  property string file: ""

  MediaPlayer {
    id: audio
    source: root.file
    audioOutput: AudioOutput {}
  }

  FileDialog {
    id: fileDialog
    onAccepted: {
      root.file = this.selectedFile.toString().substring("file://".length)
    }
  }

  RowLayout {
    id: row
    anchors.fill: parent

    Kirigami.ActionToolBar {
      display: Controls.Button.IconOnly
      Layout.maximumWidth: 80
      Layout.preferredWidth: Layout.maximumWidth
      actions: [

        Kirigami.Action {
          text: i18n("Play")
          icon.name: "media-playback-start"
          onTriggered: {
            audio.source = "file://" + root.file
            audio.play()
          }
        },

        Kirigami.Action {
          text: i18n("Select")
          icon.name: "edit"
          onTriggered: {
            fileDialog.currentFolder = "file://" + root.file.substring(0, root.file.lastIndexOf("/"))
            fileDialog.open()
          }
        }

      ]
    }

    Controls.Label {
      text: root.text
      Layout.minimumWidth: this.contentWidth
      Layout.preferredWidth: this.contentWidth > row.width / 7 ? this.contentWidth : row.width / 7
    }

    Kirigami.ActionTextField {
      id: fileField
      Layout.fillWidth: true
      text: root.file
      placeholderText: i18n("Sound File")
      rightActions: Kirigami.Action {
        icon.name: "edit-clear"
        visible: fileField.text.length > 0
        onTriggered: {
          fileField.clear();
        }
      }
      onTextChanged: {
        root.file = fileField.text
      }
    }

  }
}
