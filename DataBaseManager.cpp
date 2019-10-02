#include <QSqlRecord>
#include "DataBaseManager.h"
#include "SqlitePersistenceProvider.h"

namespace MyFinance {

DataBaseManager::DataBaseManager() :
    m_persistence_provider(nullptr)
{
    m_persistence_provider = std::make_unique<SqlitePersistenceProvider>();

    m_persistence_provider->read_data();
}

void DataBaseManager::add_account(const Account & account)
{
    QSqlRecord record = accounts_model()->record();
    record.setGenerated("id", false);
    record.setValue("name", account.name());
    record.setValue("balance", account.balance());

    accounts_model()->insertRecord(-1, record);
    accounts_model()->submitAll();
}

void DataBaseManager::add_transaction(
        double sum,
        int account_id,
        const QDate & date,
        const QTime & time)
{
    m_persistence_provider->add_transaction(sum, account_id, date, time);
}

} //namespace MyFinance
