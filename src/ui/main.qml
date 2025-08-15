import QtQuick 6.5
import QtQuick.Layouts 6.5
import org.kde.kcmutils as KCMUtils
import org.kde.kirigami 2.4 as Kirigami
import org.kde.plasma.components 3.0 as PlasmaComponents

KCMUtils.SimpleKCM {

  ColumnLayout {

    RowLayout {

      PlasmaComponents.Label {
        text: i18n("Theme:")
      }

      PlasmaComponents.ComboBox {
        Layout.fillWidth: true
        model: kcm.themes
        textRole: "display"
        editable: true
        validator: RegularExpressionValidator{ regularExpression: /[^/]+/ }
        onEditTextChanged: {
          kcm.theme = this.currentText
        }
      }

      PlasmaComponents.ToolButton {
        text: i18n("Load")
        icon.name: "document-open"
        onClicked: kcm.onLoadClicked()
      }

      PlasmaComponents.ToolButton {
        text: i18n("Save")
        icon.name: "document-save"
        onClicked: kcm.onSaveClicked()
      }

      PlasmaComponents.ToolButton {
        text: i18n("Delete")
        icon.name: "delete"
        onClicked: kcm.onDeleteClicked()
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

    // TODO:
    // Kirigami.FormLayout and FormData.label
    // https://api.kde.org/frameworks/kcmutils/html/classSimpleKCM.html

  }
}
