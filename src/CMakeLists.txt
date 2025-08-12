# ecm_qt_export_logging_category(
#     IDENTIFIER "CUSTOMSOUNDS_DEBUG"
#     CATEGORY_NAME "myproject.submodule"
#     DESCRIPTION "KCM Custom Sounds - submodule"
#     EXPORT MyProject
# )
# ecm_qt_install_logging_categories(
#     EXPORT MyProject
#     FILE myproject.categories
#     DESTINATION "${KDE_INSTALL_LOGGINGCATEGORIESDIR}"
# )


# kcmutils_generate_module_data(kcm_fonts
#     MODULE_DATA_HEADER fontsdata.h
#     MODULE_DATA_CLASS_NAME FontsData
#     SETTINGS_HEADERS fontssettings.h fontsaasettings.h
#     SETTINGS_CLASSES FontsSettings FontsAASettings
# )

set(kcm_customsounds_SRCS
    customsoundssettings.cpp
    customsoundssettings.h
)
kcmutils_add_qml_kcm(${PROJECT_NAME} ${kcm_customsounds_SRCS})
target_sources(${PROJECT_NAME} PRIVATE ${kcm_customsounds_SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Quick
    KF6::CoreAddons
    KF6::KCMUtils
    KF6::I18n
    Qt6::Multimedia

    Qt6::Quick
    Qt6::DBus
    KF6::I18n
    KF6::KCMUtilsQuick
    KF6::ConfigCore
    KF6::ConfigGui
    KF6::ConfigQml
)
