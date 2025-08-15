import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15

import org.kde.kcmutils 1.0 as KCMUtils
import org.kde.kirigami 2.7 as Kirigami

KCMUtils.SimpleKCM {
  Layout.fillWidth: true

  ColumnLayout {

    RowLayout {

      Kirigami.Heading {
        text: i18n("Theme:")
        level: 2
      }

      Kirigami.Separator {}

      Controls.ComboBox {
        Layout.fillWidth: true
        model: kcm.themes
        textRole: "display"
        editable: true
        validator: RegularExpressionValidator{ regularExpression: /[^/]+/ }
        onEditTextChanged: {
          kcm.theme = this.currentText
        }
      }

      Kirigami.ActionToolBar {
        // display: Controls.Button.IconOnly
        Layout.maximumWidth: this.visibleWidth
        Layout.preferredWidth: Layout.maximumWidth
        actions: [

          Kirigami.Action {
            text: i18n("Load")
            icon.name: "document-open"
            onTriggered: kcm.onLoadClicked()
          },

          Kirigami.Action {
            text: i18n("Save")
            icon.name: "document-save"
            onTriggered: kcm.onSaveClicked()
          },

          Kirigami.Action {
            text: i18n("Delete")
            icon.name: "delete"
            onTriggered: kcm.onDeleteClicked()
          }

        ]
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
      }
    }

  }
}
