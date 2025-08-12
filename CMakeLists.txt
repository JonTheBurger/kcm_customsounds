cmake_minimum_required(VERSION 3.16)

set(QT_MIN_VERSION "6.5.0")
set(KF6_MIN_VERSION "6.0.0")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(kcm_customsounds)

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(ECMQmlModule)
include(ECMQtDeclareLoggingCategory)
include(KDEInstallDirs)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(KDEClangFormat)

find_package(Qt6 ${QT_MIN_VERSION} CONFIG REQUIRED
    Core
    Quick
    Gui
    Multimedia
    Qml
)

find_package(KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS
    Config
    CoreAddons
    KCMUtils
    I18n
)

add_definitions(-DTRANSLATION_DOMAIN=\"${PROJECT_NAME}\")
ki18n_wrap_ui(kcm_customsounds)

ecm_qt_declare_logging_category(${PROJECT_NAME}
    HEADER ${PROJECT_NAME}_debug.h
    IDENTIFIER KCM_CUSTOMSOUNDS_DEBUG
    CATEGORY_NAME kcm_customsounds
    DESCRIPTION "kcm custom sounds"
    EXPORT CUSTOMSOUNDS
)

file(
    GLOB_RECURSE kcm_customsounds_SRCS
    LIST_DIRECTORIES false
    CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

kde_clang_format(${kcm_customsounds_SRCS})

add_subdirectory(src)
