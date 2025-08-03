#include "customsoundssettings.h"

#include <KPluginFactory>
#include <QDir>
#include <QStandardPaths>
#include <QtLogging>

K_PLUGIN_CLASS_WITH_JSON(CustomSoundsSettings, "kcm_customsounds.json") // NOLINT

CustomSoundsSettings::CustomSoundsSettings(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule(parent, data)
    , m_statusText{QStringLiteral("TESTING")}
    , m_themes{QStringLiteral("Default"), QStringLiteral("Custom")}
{
  setButtons(Help);
    const QString xdgData = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    const QString xdgSounds = xdgData + QStringLiteral("/sounds");
    const QDir soundsDir = xdgSounds;
    qWarning() << "Sound dir: " << xdgSounds;

    if (soundsDir.exists()) {
        // m_themes = soundsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Readable | QDir::Writable | QDir::Executable);
        qWarning() << "Found themes: " << m_themes;
    } else {
        QDir{xdgData}.mkdir(QStringLiteral("sounds"));
        qWarning() << "No sounds";
    }


    m_themesModel.setStringList(m_themes);
}

void CustomSoundsSettings::handleClick()
{
}

QString CustomSoundsSettings::statusText() const
{
  return m_statusText;
}

QStringListModel* CustomSoundsSettings::themes()
{
  return &m_themesModel;
}

#include "customsoundssettings.moc"
