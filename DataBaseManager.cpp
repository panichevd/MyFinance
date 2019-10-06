#include <QSqlQuery>
#include <QSqlRecord>
#include "DataBaseManager.h"
#include "SqlitePersistenceProvider.h"

namespace MyFinance {

DataBaseManager::DataBaseManager() :
    m_persistence_provider(nullptr)
{
    m_persistence_provider = std::make_unique<SqlitePersistenceProvider>();

    m_persistence_provider->read_data(m_accounts);
}

void DataBaseManager::add_account(
        const QString & name,
        double balance)
{
    // TODO: move to Persistence provider. return abstract model instead of concrete
    QSqlRecord record = accounts_model()->record();
    record.setGenerated("id", false);
    record.setValue("name", name);
    record.setValue("balance", balance);

    accounts_model()->insertRecord(-1, record);
    accounts_model()->submitAll();

    int id = accounts_model()->query().lastInsertId().toInt();
    m_accounts[name] = Account(id, name, balance);
}

bool DataBaseManager::add_transaction(
        double sum,
        const QString & account_name,
        const QDate & date,
        const QTime & time)
{
    auto it = m_accounts.find(account_name);
    if (it == m_accounts.end()) {
        return false;
    }

    m_persistence_provider->add_transaction(sum, it->second.id(), date, time);
    return true;
}

} //namespace MyFinance
