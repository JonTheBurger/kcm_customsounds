#include "SystemSound.h"

#include <utility>

#include <QStandardPaths>
#include <QtLogging>

namespace
{
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

SystemSound::SystemSound(const QString &text, const QString &file)
    : m_text{text}
    , m_file{file}
{
}

// SystemSound::SystemSound(const SystemSound &other)
//     : m_text{other.m_text}
//     , m_file{other.m_file}
// {
// }
//
// SystemSound::SystemSound(SystemSound &&other)
//     : m_text{std::move(other.m_text)}
//     , m_file{std::move(other.m_file)}
// {
// }
//
// auto SystemSound::operator=(const SystemSound &other) -> SystemSound &
// {
//     m_text = other.m_text;
//     m_file = other.m_file;
//     return *this;
// }
//
// auto SystemSound::operator=(SystemSound &&other) -> SystemSound &
// {
//     m_text = std::move(other.m_text);
//     m_file = std::move(other.m_file);
//     return *this;
// }

auto SystemSound::text() const -> QString
{
    return m_text;
}

auto SystemSound::file() const -> QString
{
    return m_file;
}

void SystemSound::setText(const QString &text)
{
    if (m_text != text) {
        m_text = text;
        Q_EMIT textChanged();
    }
}

void SystemSound::setFile(const QString &file)
{
    if (m_file != file) {
        m_file = file;
        Q_EMIT fileChanged();
    }
}

void SystemSound::resetText()
{
    setText({});
}

void SystemSound::resetFile()
{
    setFile({});
}
