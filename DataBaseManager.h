#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>

#include "IPersistenceProvider.h"

// TODO: create custom table model to work with accounts
class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager() = default;

    QSqlTableModel* & accounts_model()
    { return m_persistence_provider->model(); }

private:
    std::unique_ptr<IPersistenceProvider> m_persistence_provider;
};

#endif // DATABASEMANAGER_H
