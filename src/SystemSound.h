#pragma once

#include <QDir>
#include <QObject>
#include <QString>
#include <QStringList>

class SystemSound final : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged RESET resetText)
    Q_PROPERTY(QString file READ file WRITE setFile NOTIFY fileChanged RESET resetFile)

public:
    SystemSound() = default;
    ~SystemSound() override = default;
    SystemSound(const QString &text, const QString &file);
    // SystemSound(const SystemSound &other);
    // SystemSound(SystemSound &&);
    // auto operator=(const SystemSound &other) -> SystemSound &;
    // auto operator=(SystemSound &&) -> SystemSound &;

    static auto userDirectory() -> QDir;
    static auto userThemes() -> QStringList;
    // static auto fromUserTheme() -> QList<SystemSound>;

    [[nodiscard]] auto text() const -> QString;
    [[nodiscard]] auto file() const -> QString;

    void setText(const QString &text);
    void setFile(const QString &file);

    void resetText();
    void resetFile();

Q_SIGNALS:
    void textChanged();
    void fileChanged();

private:
    QString m_text;
    QString m_file;
};
