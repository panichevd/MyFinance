#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>

#include "IPersistenceProvider.h"

class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager() = default;

    QSqlTableModel* & accounts_model()
    { return m_persistence_provider->model(); }

    void add_account(const Account & account);

private:
    std::unique_ptr<IPersistenceProvider> m_persistence_provider;
};

#endif // DATABASEMANAGER_H
