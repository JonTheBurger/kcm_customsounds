import QtMultimedia 6.5
import QtQuick 6.5
import QtQuick.Controls 6.5
import QtQuick.Dialogs 6.5
import QtQuick.Layouts 6.5
import org.kde.kcmutils as KCMUtils
import org.kde.kirigami 2.4 as Kirigami
import org.kde.plasma.components 3.0 as PlasmaComponents

KCMUtils.SimpleKCM {
  property alias selectedId: copyStrategy.checkedButton

  ButtonGroup {
    id: copyStrategy
    buttons: header.children
  }

  ColumnLayout {
    RowLayout {
      id: header

      PlasmaComponents.ToolButton {
        icon.name: "document-open"
        text: i18n("Load")
        onClicked: {
          console.log("Load")
          kcm.handleClick()
        }
      }

      PlasmaComponents.Label {
        // text: i18n("Theme Name:")
        text: kcm.statusText
      }

      PlasmaComponents.ComboBox {
        id: themeName
        editable: true
        Layout.fillWidth: true
        validator: RegularExpressionValidator{ regularExpression: /[^/]+/ }
        model: kcm.themes
        textRole: "display"
        onEditTextChanged: {
          console.log("Theme Name changed to: " + themeName.editText)
          kcm.handleClick()
        }
      }

      PlasmaComponents.RadioButton {
        text: i18n("Copy")
        checked: true
      }

      PlasmaComponents.RadioButton {
        text: i18n("Symlink")
        checked: false
      }

      PlasmaComponents.ToolButton {
        icon.name: "document-save"
        text: i18n("Save")
        onClicked: kcm.handleClick
      }

      PlasmaComponents.ToolButton {
        icon.name: "delete"
        text: i18n("Delete")
        onClicked: {
          console.log("Delete")
          kcm.handleClick()
        }
      }

    }

    Kirigami.Separator {
      Layout.fillWidth: true
    }

    ListView {
      model: kcm.sounds
      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.preferredHeight: contentHeight
      spacing: 4

      delegate: SystemSound {
        text: model.text
        file: model.file
        width: ListView.view.width
        // anchors.margins: 4
      }
    }

    // TODO:
    // Kirigami.FormLayout and FormData.label
    // https://api.kde.org/frameworks/kcmutils/html/classSimpleKCM.html

  }
}
