#include "SystemSound.h"

#include <QCoreApplication>
#include <QStandardPaths>
#include <QtLogging>

namespace
{
auto tr(const char *str)
{
    return QCoreApplication::translate("SystemSound", str);
}

// TODO: https://techbase.kde.org/Development/Tutorials/Localization/i18n
const struct {
    QString name;
    QString hint;
} SYSTEM_SOUNDS[] = {
    {.name = tr("Alarm Clock Elapsed"), .hint = QStringLiteral("alarm-clock-elapsed")},
    {.name = tr("Audio Volume Change"), .hint = QStringLiteral("audio-volume-change")},
    {.name = tr("Battery Caution"), .hint = QStringLiteral("battery-caution")},
    {.name = tr("Battery Full"), .hint = QStringLiteral("battery-full")},
    {.name = tr("Battery Low"), .hint = QStringLiteral("battery-low")},
    {.name = tr("Bell Window System"), .hint = QStringLiteral("bell-window-system")},
    {.name = tr("Bell"), .hint = QStringLiteral("bell")},
    {.name = tr("Button Pressed Modifier"), .hint = QStringLiteral("button-pressed-modifier")},
    {.name = tr("Button Pressed"), .hint = QStringLiteral("button-pressed")},
    {.name = tr("Complete Media Burn"), .hint = QStringLiteral("complete-media-burn")},
    {.name = tr("Complete Media Error"), .hint = QStringLiteral("complete-media-error")},
    {.name = tr("Completion Fail"), .hint = QStringLiteral("completion-fail")},
    {.name = tr("Completion Partial"), .hint = QStringLiteral("completion-partial")},
    {.name = tr("Completion Rotation"), .hint = QStringLiteral("completion-rotation")},
    {.name = tr("Completion Success"), .hint = QStringLiteral("completion-success")},
    {.name = tr("Desktop Login"), .hint = QStringLiteral("desktop-login")},
    {.name = tr("Desktop Logout"), .hint = QStringLiteral("desktop-logout")},
    {.name = tr("Device Added"), .hint = QStringLiteral("device-added")},
    {.name = tr("Device Removed"), .hint = QStringLiteral("device-removed")},
    {.name = tr("Dialog Error Critical"), .hint = QStringLiteral("dialog-error-critical")},
    {.name = tr("Dialog Error Serious"), .hint = QStringLiteral("dialog-error-serious")},
    {.name = tr("Dialog Error"), .hint = QStringLiteral("dialog-error")},
    {.name = tr("Dialog Information"), .hint = QStringLiteral("dialog-information")},
    {.name = tr("Dialog Question"), .hint = QStringLiteral("dialog-question")},
    {.name = tr("Dialog Warning Auth"), .hint = QStringLiteral("dialog-warning-auth")},
    {.name = tr("Dialog Warning"), .hint = QStringLiteral("dialog-warning")},
    {.name = tr("Game Over Loser"), .hint = QStringLiteral("game-over-loser")},
    {.name = tr("Game Over Winner"), .hint = QStringLiteral("game-over-winner")},
    {.name = tr("Media Insert Request"), .hint = QStringLiteral("media-insert-request")},
    {.name = tr("Message Attention"), .hint = QStringLiteral("message-attention")},
    {.name = tr("Message Contact In"), .hint = QStringLiteral("message-contact-in")},
    {.name = tr("Message Contact Out"), .hint = QStringLiteral("message-contact-out")},
    {.name = tr("Message Highlight"), .hint = QStringLiteral("message-highlight")},
    {.name = tr("Message New Instant"), .hint = QStringLiteral("message-new-instant")},
    {.name = tr("Message Sent Instant"), .hint = QStringLiteral("message-sent-instant")},
    {.name = tr("Outcome Failure"), .hint = QStringLiteral("outcome-failure")},
    {.name = tr("Outcome Success"), .hint = QStringLiteral("outcome-success")},
    {.name = tr("Phone Incoming Call"), .hint = QStringLiteral("phone-incoming-call")},
    {.name = tr("Power Plug"), .hint = QStringLiteral("power-plug")},
    {.name = tr("Power Unplug"), .hint = QStringLiteral("power-unplug")},
    {.name = tr("Service Login"), .hint = QStringLiteral("service-login")},
    {.name = tr("Service Logout"), .hint = QStringLiteral("service-logout")},
    {.name = tr("Theme Demo"), .hint = QStringLiteral("theme-demo")},
    {.name = tr("Trash Empty"), .hint = QStringLiteral("trash-empty")},
};

auto getSoundThemes(const QDir &soundsDir) -> QStringList
{
    return soundsDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Readable | QDir::Writable | QDir::Executable);
}
} // namespace

auto SystemSound::userDirectory() -> QDir
{
    const QString xdgData = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    const QString xdgSounds = xdgData + QStringLiteral("/sounds");
    const QDir soundsDir = xdgSounds;
    if (!soundsDir.exists()) {
        QDir{xdgData}.mkdir(QStringLiteral("sounds"));
    }
    return soundsDir;
}

auto SystemSound::userThemes() -> QStringList
{
    return getSoundThemes(userDirectory());
}

auto SystemSound::fromTheme(const QString &theme) -> std::vector<std::unique_ptr<SystemSound>>
{
    auto sounds = std::vector<std::unique_ptr<SystemSound>>{};

    QDir themeDir = userDirectory() / theme / QStringLiteral("stereo");

    for (const auto &sound : SYSTEM_SOUNDS) {
        sounds.push_back(std::make_unique<SystemSound>(sound.name, sound.hint, QString()));
    }

    if (themeDir.exists()) {
        themeDir.setFilter(QDir::Files | QDir::Readable);
        qInfo() << "Searching for sounds in " << themeDir.path();

        for (const auto &sound : sounds) {
            auto files = themeDir.entryList({sound->hint() + QStringLiteral(".*")});
            if (!files.empty()) {
                qDebug() << "Found sounds: " << files << " for " << sound->hint();
                sound->setFile(themeDir.filePath(files[0]));
            } else {
                qInfo() << "No sounds for " << sound->hint() << " in " << themeDir.path();
            }
        }
    } else {
        qInfo() << "Theme " << themeDir.path() << " does not exist";
    }

    if (!theme.isEmpty()) {
        themeDir.mkpath(themeDir.absolutePath());
    }
    return sounds;
}

SystemSound::SystemSound(const QString &text, const QString &hint, const QString &file)
    : m_text{text}
    , m_hint{hint}
    , m_file{file}
{
}

auto SystemSound::text() const -> QString
{
    return m_text;
}

auto SystemSound::hint() const -> QString
{
    return m_hint;
}

auto SystemSound::file() const -> QString
{
    return m_file;
}

void SystemSound::setFile(const QString &file)
{
    if (m_file != file) {
        m_file = file;
        Q_EMIT fileChanged();
    }
}

auto operator<<(QDebug dbg, const SystemSound &self) -> QDebug
{
    dbg.nospace() << "SystemSound(" << self.text() << ", " << self.hint() << ", " << self.file() << ")";
    return dbg.space();
}

auto operator/(const QDir &dir, const QString &subdir) -> QDir
{
    return dir.filePath(subdir);
}
