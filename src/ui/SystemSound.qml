import QtMultimedia 6.5
import QtQuick 6.5
import QtQuick.Dialogs 6.5
import QtQuick.Layouts 6.5
import org.kde.plasma.components 3.0 as PlasmaComponents

Item {
  id: root
  height: row.implicitHeight

  property string text: ""
  property string file: ""

  RowLayout {
    id: row
    anchors.fill: parent

    Layout.fillWidth: true

    MediaPlayer {
      id: audio
      source: root.file
      audioOutput: AudioOutput {}
    }

    PlasmaComponents.ToolButton {
      icon.name: "media-playback-start"
      onClicked: {
        audio.source = "file://" + root.file
        audio.play()
      }
    }

    PlasmaComponents.ToolButton {
      icon.name: "edit"
      onClicked: {
        fileDialog.currentFolder = "file://" + root.file.substring(0, root.file.lastIndexOf("/"))
        fileDialog.open()
      }
    }

    FileDialog {
      id: fileDialog
      onAccepted: {
        root.file = this.selectedFile.toString().substring("file://".length)
      }
    }

    PlasmaComponents.Label {
      text: root.text
      Layout.preferredWidth: 200
    }

    PlasmaComponents.TextField {
      text: root.file
      Layout.fillWidth: true
      onTextChanged: {
        root.file = this.text
      }

    }

    PlasmaComponents.ToolButton {
      icon.name: "reload"
      onClicked: {
        root.file = ""
      }
    }

  }
}
