#include "CustomSoundsSettings.h"

#include <KPluginFactory>
#include <QDir>
#include <QStandardPaths>
#include <QtLogging>

K_PLUGIN_CLASS_WITH_JSON(CustomSoundsSettings, "kcm_customsounds.json") // NOLINT

CustomSoundsSettings::CustomSoundsSettings(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule(parent, data)
    , m_statusText{QStringLiteral("TESTING")}
    , m_themes{SystemSound::userThemes()}
    , m_themesModel{m_themes}
    , m_soundsModel{SystemSound::fromTheme(QStringLiteral("jon"))}
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

auto CustomSoundsSettings::sounds() -> SystemSoundModel *
{
    return &m_soundsModel;
}

#include "CustomSoundsSettings.moc"
