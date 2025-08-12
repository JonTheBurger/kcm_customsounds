#pragma once

#include <KQuickConfigModule>
#include <QStringList>
#include <QStringListModel>

class CustomSoundsSettings : public KQuickConfigModule
{
    Q_OBJECT
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(QStringListModel *themes READ themes NOTIFY themesChanged)

public:
    CustomSoundsSettings(QObject *parent, const KPluginMetaData &data);

    Q_INVOKABLE void handleClick();
    [[nodiscard]] auto statusText() const -> QString;
    auto themes() -> QStringListModel *;

Q_SIGNALS:
    void statusTextChanged();
    void themesChanged();

private:
    QString m_statusText;
    QStringList m_themes;
    QStringListModel m_themesModel;
};
