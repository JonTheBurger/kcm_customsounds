import QtQuick 6.5
import QtQuick.Controls 6.5
import QtQuick.Layouts 6.5
import org.kde.kcmutils as KCMUtils
import org.kde.kirigami 2.4 as Kirigami
import org.kde.plasma.components 3.0 as PlasmaComponents

// import example 1.0

KCMUtils.SimpleKCM {
  // id: kcm

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
        // editable: true
        Layout.fillWidth: true
        // validator: RegularExpressionValidator{ regularExpression: /[^/]+/ }
        model: kcm.themes
        // model: ["A", "B", "C"]
        // textRole: "display"
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
          kcm.handleClick
        }
      }

    }

    Kirigami.Separator {
      Layout.fillWidth: true
    }

    SystemSound {
      text: i18n("Alarm Clock Elapsed")
      sound: "alarm-clock-elapsed"
    }
    SystemSound {
      text: i18n("Audio Volume Change")
      sound: "audio-volume-change"
    }
    SystemSound {
      text: i18n("Battery Caution")
      sound: "battery-caution"
    }
    SystemSound {
      text: i18n("Battery Full")
      sound: "battery-full"
    }
    SystemSound {
      text: i18n("Battery Low")
      sound: "battery-low"
    }
    SystemSound {
      text: i18n("Bell Window System")
      sound: "bell-window-system"
    }
    SystemSound {
      text: i18n("Bell")
      sound: "bell"
    }
    SystemSound {
      text: i18n("Button Pressed Modifier")
      sound: "button-pressed-modifier"
    }
    SystemSound {
      text: i18n("Button Pressed")
      sound: "button-pressed"
    }
    SystemSound {
      text: i18n("Complete Media Burn")
      sound: "complete-media-burn"
    }
    SystemSound {
      text: i18n("Complete Media Error")
      sound: "complete-media-error"
    }
    SystemSound {
      text: i18n("Completion Fail")
      sound: "completion-fail"
    }
    SystemSound {
      text: i18n("Completion Partial")
      sound: "completion-partial"
    }
    SystemSound {
      text: i18n("Completion Rotation")
      sound: "completion-rotation"
    }
    SystemSound {
      text: i18n("Completion Success")
      sound: "completion-success"
    }
    SystemSound {
      text: i18n("Desktop Login")
      sound: "desktop-login"
    }
    SystemSound {
      text: i18n("Desktop Logout")
      sound: "desktop-logout"
    }
    SystemSound {
      text: i18n("Device Added")
      sound: "device-added"
    }
    SystemSound {
      text: i18n("Device Removed")
      sound: "device-removed"
    }
    SystemSound {
      text: i18n("Dialog Error Critical")
      sound: "dialog-error-critical"
    }
    SystemSound {
      text: i18n("Dialog Error Serious")
      sound: "dialog-error-serious"
    }
    SystemSound {
      text: i18n("Dialog Error")
      sound: "dialog-error"
    }
    SystemSound {
      text: i18n("Dialog Information")
      sound: "dialog-information"
    }
    SystemSound {
      text: i18n("Dialog Question")
      sound: "dialog-question"
    }
    SystemSound {
      text: i18n("Dialog Warning Auth")
      sound: "dialog-warning-auth"
    }
    SystemSound {
      text: i18n("Dialog Warning")
      sound: "dialog-warning"
    }
    SystemSound {
      text: i18n("Game Over Loser")
      sound: "game-over-loser"
    }
    SystemSound {
      text: i18n("Game Over Winner")
      sound: "game-over-winner"
    }
    SystemSound {
      text: i18n("Media Insert Request")
      sound: "media-insert-request"
    }
    SystemSound {
      text: i18n("Message Attention")
      sound: "message-attention"
    }
    SystemSound {
      text: i18n("Message Contact In")
      sound: "message-contact-in"
    }
    SystemSound {
      text: i18n("Message Contact Out")
      sound: "message-contact-out"
    }
    SystemSound {
      text: i18n("Message Highlight")
      sound: "message-highlight"
    }
    SystemSound {
      text: i18n("Message New Instant")
      sound: "message-new-instant"
    }
    SystemSound {
      text: i18n("Message Sent Instant")
      sound: "message-sent-instant"
    }
    SystemSound {
      text: i18n("Outcome Failure")
      sound: "outcome-failure"
    }
    SystemSound {
      text: i18n("Outcome Success")
      sound: "outcome-success"
    }
    SystemSound {
      text: i18n("Phone Incoming Call")
      sound: "phone-incoming-call"
    }
    SystemSound {
      text: i18n("Power Plug")
      sound: "power-plug"
    }
    SystemSound {
      text: i18n("Power Unplug")
      sound: "power-unplug"
    }
    SystemSound {
      text: i18n("Service Login")
      sound: "service-login"
    }
    SystemSound {
      text: i18n("Service Logout")
      sound: "service-logout"
    }
    SystemSound {
      text: i18n("Theme Demo")
      sound: "theme-demo"
    }
    SystemSound {
      text: i18n("Trash Empty")
      sound: "trash-empty"
    }
  }
}
