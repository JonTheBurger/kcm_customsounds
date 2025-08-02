kcmutils_add_qml_kcm(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
   customsoundssettings.cpp
   customsoundssettings.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Quick
    KF6::CoreAddons
    KF6::KCMUtils
    KF6::I18n
)
