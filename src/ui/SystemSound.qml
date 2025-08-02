import QtQuick 6.5
import QtQuick.Layouts 6.5
import org.kde.plasma.components 3.0 as PlasmaComponents

RowLayout {
  id: root
  property string text

  PlasmaComponents.ToolButton {
    icon.name: "media-playback-start"
    Layout.preferredWidth: 40
  }
  PlasmaComponents.ToolButton {
    icon.name: "edit"
    Layout.preferredWidth: 40
    onClicked: {
      console.log("Edit button clicked")
    }
  }
  PlasmaComponents.Label {
    text: root.text
    Layout.fillWidth: true
  }
  PlasmaComponents.TextField {
    text: "Hello"
    Layout.fillWidth: true
    Layout.preferredWidth: 200
    onTextChanged: {
      // root.text = text
    }
  }
  PlasmaComponents.ToolButton {
    icon.name: "media-playback-start"
    Layout.preferredWidth: 40
  }
}
