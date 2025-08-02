#pragma once

#include <KQuickConfigModule>

class CustomSoundsSettings : public KQuickConfigModule
{
    Q_OBJECT
    public:
        CustomSoundsSettings(QObject *parent, const KPluginMetaData &data);
};
