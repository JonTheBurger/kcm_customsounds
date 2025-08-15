#pragma once

#include <memory>
#include <vector>

#include <QAbstractListModel>

#include "SystemSound.h"

class SystemSoundModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role : uint16_t {
        TextRole = Qt::UserRole + 1,
        FileRole,
    };

    explicit SystemSoundModel(std::vector<std::unique_ptr<SystemSound>> sounds, QObject *parent = nullptr);
    auto reset(std::vector<std::unique_ptr<SystemSound>> sounds) -> void;
    [[nodiscard]] auto raw() const noexcept -> const std::vector<std::unique_ptr<SystemSound>> &;

    [[nodiscard]] auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int override;
    [[nodiscard]] auto data(const QModelIndex &index, int role = Qt::DisplayRole) const -> QVariant override;
    auto setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) -> bool override;
    [[nodiscard]] auto flags(const QModelIndex &index) const -> Qt::ItemFlags override;
    [[nodiscard]] auto roleNames() const -> QHash<int, QByteArray> override;

private:
    std::vector<std::unique_ptr<SystemSound>> m_sounds;
};
