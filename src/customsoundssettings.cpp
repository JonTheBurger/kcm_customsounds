#include "customsoundssettings.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(CustomSoundsSettings, "kcm_customsounds.json")

CustomSoundsSettings::CustomSoundsSettings(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule(parent, data)
{
    setButtons(Help | Apply | Default);
}

#include "customsoundssettings.moc"
