#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>

#include "IPersistenceProvider.h"

class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager() = default;

    const QVector<Account> & accounts() const
    { return m_persistence_provider->accounts(); }

private:
    std::unique_ptr<IPersistenceProvider> m_persistence_provider;
};

#endif // DATABASEMANAGER_H
