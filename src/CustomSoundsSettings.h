#pragma once

#include <KQuickConfigModule>
#include <QStringList>
#include <QStringListModel>

#include "SystemSoundModel.h"

class CustomSoundsSettings : public KQuickConfigModule
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme)
    Q_PROPERTY(QStringListModel *themes READ themes NOTIFY themesChanged)
    Q_PROPERTY(SystemSoundModel *sounds READ sounds NOTIFY soundsChanged)

public:
    CustomSoundsSettings(QObject *parent, const KPluginMetaData &data);

    auto setTheme(const QString& theme) -> void;
    [[nodiscard]] auto theme() const -> QString;
    [[nodiscard]] auto themes() -> QStringListModel *;
    [[nodiscard]] auto sounds() -> SystemSoundModel *;

    Q_INVOKABLE void onLoadClicked();
    Q_INVOKABLE void onSaveClicked();
    Q_INVOKABLE void onDeleteClicked();

Q_SIGNALS:
    void themesChanged();
    void soundsChanged();

private:
    QString m_theme;
    QStringListModel m_themesModel;
    SystemSoundModel m_soundsModel;
};
