#include "DataBaseManager.h"
#include "PostgreSqlPersistenceProvider.h"
#include "SqlitePersistenceProvider.h"

DataBaseManager::DataBaseManager() :
    m_persistence_provider(nullptr)
{
    m_persistence_provider = std::make_unique<SqlitePersistenceProvider>();

    m_persistence_provider->read_data();
}
