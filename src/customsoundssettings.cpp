#include "customsoundssettings.h"

#include <KPluginFactory>
#include <QDir>
#include <QStandardPaths>
#include <QtLogging>

K_PLUGIN_CLASS_WITH_JSON(CustomSoundsSettings, "kcm_customsounds.json") // NOLINT

namespace {
auto getSoundsDir() -> QDir
{
    const QString xdgData = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    const QString xdgSounds = xdgData + QStringLiteral("/sounds");
    const QDir soundsDir = xdgSounds;
    if (!soundsDir.exists()) {
        QDir{xdgData}.mkdir(QStringLiteral("sounds"));
    }
    return soundsDir;
}

auto getSoundThemes() -> QStringList
{
    const QDir soundsDir = getSoundsDir();
    qWarning() << "Sound dir: " << soundsDir;
    return soundsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Readable | QDir::Writable | QDir::Executable);
}
} // namespace

CustomSoundsSettings::CustomSoundsSettings(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule(parent, data)
    , m_statusText{QStringLiteral("TESTING")}
    , m_themes{getSoundThemes()}
    , m_themesModel{m_themes}
{
    setButtons(Help);
}

auto CustomSoundsSettings::handleClick() -> void
{
    qWarning() << "handleClick()";
}

auto CustomSoundsSettings::statusText() const -> QString
{
    return m_statusText;
}

auto CustomSoundsSettings::themes() -> QStringListModel *
{
    return &m_themesModel;
}

#include "customsoundssettings.moc"
