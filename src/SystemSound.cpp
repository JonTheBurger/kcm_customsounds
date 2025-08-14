#include "SystemSound.h"

#include <filesystem>
#include <utility>

#include <QStandardPaths>
#include <QtLogging>

namespace fs = std::filesystem;

namespace
{
constexpr struct {
    QStringView name;
    QStringView hint;
} SYSTEM_SOUNDS[] = {
    // TODO: tr()
    {.name = u"Alarm Clock Elapsed", .hint = u"alarm-clock-elapsed"},
    {.name = u"Audio Volume Change", .hint = u"audio-volume-change"},
    {.name = u"Battery Caution", .hint = u"battery-caution"},
    {.name = u"Battery Full", .hint = u"battery-full"},
    {.name = u"Battery Low", .hint = u"battery-low"},
    {.name = u"Bell Window System", .hint = u"bell-window-system"},
    {.name = u"Bell", .hint = u"bell"},
    {.name = u"Button Pressed Modifier", .hint = u"button-pressed-modifier"},
    {.name = u"Button Pressed", .hint = u"button-pressed"},
    {.name = u"Complete Media Burn", .hint = u"complete-media-burn"},
    {.name = u"Complete Media Error", .hint = u"complete-media-error"},
    {.name = u"Completion Fail", .hint = u"completion-fail"},
    {.name = u"Completion Partial", .hint = u"completion-partial"},
    {.name = u"Completion Rotation", .hint = u"completion-rotation"},
    {.name = u"Completion Success", .hint = u"completion-success"},
    {.name = u"Desktop Login", .hint = u"desktop-login"},
    {.name = u"Desktop Logout", .hint = u"desktop-logout"},
    {.name = u"Device Added", .hint = u"device-added"},
    {.name = u"Device Removed", .hint = u"device-removed"},
    {.name = u"Dialog Error Critical", .hint = u"dialog-error-critical"},
    {.name = u"Dialog Error Serious", .hint = u"dialog-error-serious"},
    {.name = u"Dialog Error", .hint = u"dialog-error"},
    {.name = u"Dialog Information", .hint = u"dialog-information"},
    {.name = u"Dialog Question", .hint = u"dialog-question"},
    {.name = u"Dialog Warning Auth", .hint = u"dialog-warning-auth"},
    {.name = u"Dialog Warning", .hint = u"dialog-warning"},
    {.name = u"Game Over Loser", .hint = u"game-over-loser"},
    {.name = u"Game Over Winner", .hint = u"game-over-winner"},
    {.name = u"Media Insert Request", .hint = u"media-insert-request"},
    {.name = u"Message Attention", .hint = u"message-attention"},
    {.name = u"Message Contact In", .hint = u"message-contact-in"},
    {.name = u"Message Contact Out", .hint = u"message-contact-out"},
    {.name = u"Message Highlight", .hint = u"message-highlight"},
    {.name = u"Message New Instant", .hint = u"message-new-instant"},
    {.name = u"Message Sent Instant", .hint = u"message-sent-instant"},
    {.name = u"Outcome Failure", .hint = u"outcome-failure"},
    {.name = u"Outcome Success", .hint = u"outcome-success"},
    {.name = u"Phone Incoming Call", .hint = u"phone-incoming-call"},
    {.name = u"Power Plug", .hint = u"power-plug"},
    {.name = u"Power Unplug", .hint = u"power-unplug"},
    {.name = u"Service Login", .hint = u"service-login"},
    {.name = u"Service Logout", .hint = u"service-logout"},
    {.name = u"Theme Demo", .hint = u"theme-demo"},
    {.name = u"Trash Empty", .hint = u"trash-empty"},
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

// auto SystemSound::fromUserTheme() -> QList<SystemSound>
// {
//     QList<SystemSound> sounds;
//     sounds.emplace_back(QStringLiteral("Alarm Clock"), QStringLiteral("/home/jon/.local/share/sounds/jon/stereo/alarm-clock.oga"));
//     return sounds;
// }

auto SystemSound::fromTheme(QStringView theme) -> std::vector<std::unique_ptr<SystemSound>>
{
    auto sounds = std::vector<std::unique_ptr<SystemSound>>{};

    QDir userDir = userDirectory();
    auto userPath = userDir.filesystemAbsolutePath();
    for (const auto &sound : SYSTEM_SOUNDS) {
        // TODO: Find sound
        sounds.push_back(std::make_unique<SystemSound>(sound.name.toString(), sound.hint.toString(), QString()));
    }

    return sounds;
}

SystemSound::SystemSound(const QString &text, const QString &hint, const QString &file)
    : m_text{text}
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
