#pragma once

#include <memory>
#include <qstringview.h>
#include <vector>

#include <QDir>
#include <QObject>
#include <QString>
#include <QStringList>

class SystemSound final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text CONSTANT)
    Q_PROPERTY(QString hint READ hint CONSTANT)
    Q_PROPERTY(QString file READ file WRITE setFile NOTIFY fileChanged)

public:
    SystemSound() = default;
    SystemSound(const QString &text, const QString &hint, const QString &file);

    /** @returns The directory containing user sound themes (usually `~/.local/share/sounds`).
     * It will be created if it does not exist.
     */
    static auto userDirectory() -> QDir;

    /** @returns A list of all existing user sound themes.
     */
    static auto userThemes() -> QStringList;

    // static auto fromUserTheme() -> QList<SystemSound>;

    /** Look up a user theme by name and return a list of sounds.
     *
     * @param theme Name of the user theme to look up.
     * @returns SystemSound entries for every system sound type.
     * If a theme exists but does not contain a particular sound, that sound
     * will be returned with an empty file().
     */
    static auto fromTheme(const QString &theme) -> std::vector<std::unique_ptr<SystemSound>>;

    /// text Display name of the sound, translatable.
    [[nodiscard]] auto text() const -> QString;

    /// hint Name of the sound file, without any extensions. Used to lookup the file.
    [[nodiscard]] auto hint() const -> QString;

    /// text Path containing system sound.
    [[nodiscard]] auto file() const -> QString;

    void setFile(const QString &file);

Q_SIGNALS:
    void fileChanged();

private:
    QString m_text;
    QString m_hint;
    QString m_file;
};

auto operator<<(QDebug dbg, const SystemSound &self) -> QDebug;
auto operator/(const QDir &dir, const QString &subdir) -> QDir;
