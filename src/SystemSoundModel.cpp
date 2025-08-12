#include "SystemSoundModel.h"

#include <QtLogging>

// SystemSoundModel::SystemSoundModel(const QList<SystemSound> &sounds, QObject *parent)
SystemSoundModel::SystemSoundModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_sounds{}
{
    m_sounds.push_back(
        std::make_unique<SystemSound>(QStringLiteral("Alarm Clock"), QStringLiteral("/home/jon/.local/share/sounds/jon/stereo/alarm-clock.oga")));
}

auto SystemSoundModel::rowCount(const QModelIndex &parent) const -> int
{
    Q_UNUSED(parent);
    return static_cast<int>(m_sounds.size());
}

auto SystemSoundModel::data(const QModelIndex &index, int role) const -> QVariant
{
    if (!index.isValid() || index.row() < 0 || index.row() >= static_cast<int>(m_sounds.size())) {
        return {};
    }

    switch (role) {
    case SystemSoundModel::Role::TextRole:
        return m_sounds[index.row()]->text();
    case SystemSoundModel::Role::FileRole:
        return m_sounds[index.row()]->file();
    }
    return {};
}

auto SystemSoundModel::setData(const QModelIndex &index, const QVariant &value, int role) -> bool
{
    if (!index.isValid() || index.row() < 0 || index.row() >= static_cast<int>(m_sounds.size())) {
        return false;
    }

    if (data(index, role) != value) {
        switch (role) {
        case SystemSoundModel::Role::TextRole:
            m_sounds[index.row()]->setText(value.toString());
            break;
        case SystemSoundModel::Role::FileRole:
            m_sounds[index.row()]->setFile(value.toString());
            break;
        }

        Q_EMIT dataChanged(index, index, {role});
        return true;
    }

    return false;
}

auto SystemSoundModel::flags(const QModelIndex &index) const -> Qt::ItemFlags
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable; // Placeholder for actual implementation
}

auto SystemSoundModel::roleNames() const -> QHash<int, QByteArray>
{
    return {
        {static_cast<int>(Role::FileRole), "file"},
        {static_cast<int>(Role::TextRole), "text"},
    };
}
