#include "SystemSound.h"

#include <QStandardPaths>
#include <QtLogging>

namespace
{
auto operator/(const QDir &dir, const QString &subdir) -> QDir
{
    return QDir(dir.filePath(subdir));
}

// TODO: tr()
const struct {
    QString name;
    QString hint;
} SYSTEM_SOUNDS[] = {
    {.name = QStringLiteral("Alarm Clock Elapsed"), .hint = QStringLiteral("alarm-clock-elapsed")},
    {.name = QStringLiteral("Audio Volume Change"), .hint = QStringLiteral("audio-volume-change")},
    {.name = QStringLiteral("Battery Caution"), .hint = QStringLiteral("battery-caution")},
    {.name = QStringLiteral("Battery Full"), .hint = QStringLiteral("battery-full")},
    {.name = QStringLiteral("Battery Low"), .hint = QStringLiteral("battery-low")},
    {.name = QStringLiteral("Bell Window System"), .hint = QStringLiteral("bell-window-system")},
    {.name = QStringLiteral("Bell"), .hint = QStringLiteral("bell")},
    {.name = QStringLiteral("Button Pressed Modifier"), .hint = QStringLiteral("button-pressed-modifier")},
    {.name = QStringLiteral("Button Pressed"), .hint = QStringLiteral("button-pressed")},
    {.name = QStringLiteral("Complete Media Burn"), .hint = QStringLiteral("complete-media-burn")},
    {.name = QStringLiteral("Complete Media Error"), .hint = QStringLiteral("complete-media-error")},
    {.name = QStringLiteral("Completion Fail"), .hint = QStringLiteral("completion-fail")},
    {.name = QStringLiteral("Completion Partial"), .hint = QStringLiteral("completion-partial")},
    {.name = QStringLiteral("Completion Rotation"), .hint = QStringLiteral("completion-rotation")},
    {.name = QStringLiteral("Completion Success"), .hint = QStringLiteral("completion-success")},
    {.name = QStringLiteral("Desktop Login"), .hint = QStringLiteral("desktop-login")},
    {.name = QStringLiteral("Desktop Logout"), .hint = QStringLiteral("desktop-logout")},
    {.name = QStringLiteral("Device Added"), .hint = QStringLiteral("device-added")},
    {.name = QStringLiteral("Device Removed"), .hint = QStringLiteral("device-removed")},
    {.name = QStringLiteral("Dialog Error Critical"), .hint = QStringLiteral("dialog-error-critical")},
    {.name = QStringLiteral("Dialog Error Serious"), .hint = QStringLiteral("dialog-error-serious")},
    {.name = QStringLiteral("Dialog Error"), .hint = QStringLiteral("dialog-error")},
    {.name = QStringLiteral("Dialog Information"), .hint = QStringLiteral("dialog-information")},
    {.name = QStringLiteral("Dialog Question"), .hint = QStringLiteral("dialog-question")},
    {.name = QStringLiteral("Dialog Warning Auth"), .hint = QStringLiteral("dialog-warning-auth")},
    {.name = QStringLiteral("Dialog Warning"), .hint = QStringLiteral("dialog-warning")},
    {.name = QStringLiteral("Game Over Loser"), .hint = QStringLiteral("game-over-loser")},
    {.name = QStringLiteral("Game Over Winner"), .hint = QStringLiteral("game-over-winner")},
    {.name = QStringLiteral("Media Insert Request"), .hint = QStringLiteral("media-insert-request")},
    {.name = QStringLiteral("Message Attention"), .hint = QStringLiteral("message-attention")},
    {.name = QStringLiteral("Message Contact In"), .hint = QStringLiteral("message-contact-in")},
    {.name = QStringLiteral("Message Contact Out"), .hint = QStringLiteral("message-contact-out")},
    {.name = QStringLiteral("Message Highlight"), .hint = QStringLiteral("message-highlight")},
    {.name = QStringLiteral("Message New Instant"), .hint = QStringLiteral("message-new-instant")},
    {.name = QStringLiteral("Message Sent Instant"), .hint = QStringLiteral("message-sent-instant")},
    {.name = QStringLiteral("Outcome Failure"), .hint = QStringLiteral("outcome-failure")},
    {.name = QStringLiteral("Outcome Success"), .hint = QStringLiteral("outcome-success")},
    {.name = QStringLiteral("Phone Incoming Call"), .hint = QStringLiteral("phone-incoming-call")},
    {.name = QStringLiteral("Power Plug"), .hint = QStringLiteral("power-plug")},
    {.name = QStringLiteral("Power Unplug"), .hint = QStringLiteral("power-unplug")},
    {.name = QStringLiteral("Service Login"), .hint = QStringLiteral("service-login")},
    {.name = QStringLiteral("Service Logout"), .hint = QStringLiteral("service-logout")},
    {.name = QStringLiteral("Theme Demo"), .hint = QStringLiteral("theme-demo")},
    {.name = QStringLiteral("Trash Empty"), .hint = QStringLiteral("trash-empty")},
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
        qInfo() << "Searching for sounds in " << themeDir;

        for (const auto &sound : sounds) {
            auto files = themeDir.entryList({sound->hint() + QStringLiteral(".*")});
            if (!files.empty()) {
                qInfo() << "Found sounds: " << files << " for " << sound->hint();
                sound->setFile(themeDir.filePath(files[0]));
            } else {
                qInfo() << "No sounds for " << sound->hint() << " in " << themeDir;
            }
        }
    } else {
        qInfo() << "Theme " << themeDir << " does not exist";
    }

    themeDir.mkpath(themeDir.absolutePath());
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

void SystemSound::resetFile()
{
    setFile({});
}

auto operator<<(QDebug dbg, const SystemSound &self) -> QDebug
{
    dbg.nospace() << "SystemSound(" << self.text() << ", " << self.hint() << ", " << self.file() << ")";
    return dbg.space();
}
