#include "CustomSoundsSettings.h"

#include <KPluginFactory>
#include <QDir>
#include <QStandardPaths>
#include <QtLogging>

K_PLUGIN_CLASS_WITH_JSON(CustomSoundsSettings, "kcm_customsounds.json") // NOLINT

CustomSoundsSettings::CustomSoundsSettings(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule(parent, data)
    , m_themesModel{SystemSound::userThemes()} // TODO: Get current theme
    , m_soundsModel{SystemSound::fromTheme(QString())}
{
    setButtons(Help);
}

auto CustomSoundsSettings::setTheme(const QString &theme) -> void
{
    m_theme = theme;
}

auto CustomSoundsSettings::theme() const -> QString
{
    return m_theme;
}

auto CustomSoundsSettings::themes() -> QStringListModel *
{
    return &m_themesModel;
}

auto CustomSoundsSettings::sounds() -> SystemSoundModel *
{
    return &m_soundsModel;
}

void CustomSoundsSettings::onLoadClicked()
{
    m_soundsModel.reset(SystemSound::fromTheme(theme()));
}

void CustomSoundsSettings::onSaveClicked()
{
    qWarning() << "onSaveClicked()";
    // TODO: Save to disk
}

void CustomSoundsSettings::onDeleteClicked()
{
    qWarning() << "onDeleteClicked()";
    // TODO: Remove from disk
    // TODO: Remove from m_themesModel
}

#include "CustomSoundsSettings.moc"
