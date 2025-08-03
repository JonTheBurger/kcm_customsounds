import QtQuick 6.5
import QtQuick.Layouts 6.5
import org.kde.plasma.components 3.0 as PlasmaComponents

RowLayout {
  id: root

  property string text: ""
  property string sound: ""
  property string file: ""

  PlasmaComponents.ToolButton {
    icon.name: "media-playback-start"
  }

  PlasmaComponents.ToolButton {
    icon.name: "edit"
    onClicked: {
      console.log("Edit button clicked")
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
      // root.text = text
    }
  }

  PlasmaComponents.ToolButton {
    icon.name: "reload"
  }

}
