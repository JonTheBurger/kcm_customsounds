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
    Q_PROPERTY(QString text READ text)
    Q_PROPERTY(QString hint READ hint)
    Q_PROPERTY(QString file READ file WRITE setFile NOTIFY fileChanged RESET resetFile)

public:
    SystemSound() = default;
    SystemSound(const QString &text, const QString &hint, const QString &file);

    static auto userDirectory() -> QDir;
    static auto userThemes() -> QStringList;
    // static auto fromUserTheme() -> QList<SystemSound>;

    /** Look up a user theme by name and return a list of sounds.
     *
     * @param theme Name of the user theme to look up.
     * @returns SystemSound entries for every system sound type.
     * If a theme exists but does not contain a particular sound, that sound
     * will be returned with an empty file().
     */
    static auto fromTheme(QStringView theme) -> std::vector<std::unique_ptr<SystemSound>>;

    /// text Display name of the sound, translatable.
    [[nodiscard]] auto text() const -> QString;
    /// hint Name of the sound file, without any extensions. Used to lookup the file.
    [[nodiscard]] auto hint() const -> QString;
    /// text Path containing system sound.
    [[nodiscard]] auto file() const -> QString;

    void setFile(const QString &file);

    void resetFile();

Q_SIGNALS:
    void fileChanged();

private:
    QString m_text;
    QString m_hint;
    QString m_file;
};
