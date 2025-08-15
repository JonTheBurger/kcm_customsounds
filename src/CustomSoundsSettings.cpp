#include "CustomSoundsSettings.h"
#include "SystemSound.h"

#include <KPluginFactory>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QStringBuilder>
#include <QTemporaryDir>
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
    if (theme != m_theme) {
        m_theme = theme;
        Q_EMIT themeChanged();
    }
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
    using namespace Qt::StringLiterals;
    auto userDir = SystemSound::userDirectory();
    QString bkp = u"."_s % theme() % u".bkp"_s;

    // Backup dir
    userDir.mkdir(theme()); // first can fail if it exists
    bool ok = userDir.rename(theme(), bkp);
    if (!ok) {
        qWarning() << "Failed to backup " << theme() << " dir";
        return;
    }
    ok = userDir.mkdir(theme());
    if (!ok) {
        qWarning() << "Failed to make " << theme() << " dir";
        return;
    }

    QDir themeDir = userDir / theme();
    ok = themeDir.mkdir(u"stereo"_s);
    if (!ok) {
        qWarning() << "Failed to make " << theme() << "/stereo dir";
        return;
    }
    QDir soundDir = themeDir / u"stereo"_s;

    for (const auto &sound : this->m_soundsModel.raw()) {
        auto src = sound->file();
        auto dst = soundDir.filePath(QDir{src}.dirName());
        qInfo() << "Copying " << src << " to " << dst;

        ok = QFile::copy(src, dst);
        if (!ok) {
            qWarning() << "Copy failed";
            break;
        }
    }

    if (!ok) {
        qWarning() << "Attempting to restore original";
        themeDir.removeRecursively();
        userDir.rename(bkp, theme());
    }
    // TODO: This doesn't cleanup early a la destructor or handle load+save same theme
    (userDir / bkp).removeRecursively();
}

void CustomSoundsSettings::onDeleteClicked()
{
    auto themeDir = SystemSound::userDirectory() / theme();
    if (themeDir.removeRecursively()) {
        qInfo() << "Deleted " << themeDir;
    } else {
        qWarning() << "Failed to delete " << themeDir;
    }

    auto row = m_themesModel.stringList().indexOf(theme());
    if (row != -1) {
        Q_ASSERT(INT_MIN < row && row < INT_MAX);
        m_themesModel.removeRows(static_cast<int>(row), 1);
    }
}

#include "CustomSoundsSettings.moc"
