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
    int id = 0;
    if (m_persistence_provider->add_account(name, balance, id)) {
        m_accounts[name] = Account(id, name, balance);
    }
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
    int account_id = it->second.id();

    return m_persistence_provider->add_transaction(sum, account_id, date, time);
}

bool DataBaseManager::add_transfer(
        double sum,
        const QString & account_name,
        const QString & account2_name,
        const QDate & date,
        const QTime & time)
{
    auto it = m_accounts.find(account_name);
    if (it == m_accounts.end()) {
        return false;
    }
    int account_id = it->second.id();

    it = m_accounts.find(account2_name);
    if (it == m_accounts.end()) {
        return false;
    }
    int account2_id = it->second.id();

    return m_persistence_provider->add_transfer(
                sum, account_id, account2_id, date, time);
}

} //namespace MyFinance
