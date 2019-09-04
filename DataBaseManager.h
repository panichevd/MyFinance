#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>

#include "IPersistenceProvider.h"

class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager() = default;

private:
    std::unique_ptr<IPersistenceProvider> m_persistence_provider;
};

#endif // DATABASEMANAGER_H
