#pragma once

#include <KQuickConfigModule>
#include <QStringList>
#include <QStringListModel>

#include "SystemSoundModel.h"

class CustomSoundsSettings : public KQuickConfigModule
{
    Q_OBJECT
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(QStringListModel *themes READ themes NOTIFY themesChanged)
    Q_PROPERTY(SystemSoundModel *sounds READ sounds NOTIFY soundsChanged)

public:
    CustomSoundsSettings(QObject *parent, const KPluginMetaData &data);

    Q_INVOKABLE void handleClick();
    [[nodiscard]] auto statusText() const -> QString;
    [[nodiscard]] auto themes() -> QStringListModel *;
    [[nodiscard]] auto sounds() -> SystemSoundModel *;

Q_SIGNALS:
    void statusTextChanged();
    void themesChanged();
    void soundsChanged();

private:
    QString m_statusText;
    QStringList m_themes;
    QStringListModel m_themesModel;
    SystemSoundModel m_soundsModel;
};
