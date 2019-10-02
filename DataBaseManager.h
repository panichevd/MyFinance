#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>

#include "IPersistenceProvider.h"

namespace MyFinance {

class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager() = default;

    QSqlTableModel* & accounts_model()
    { return m_persistence_provider->model(); }

    IPersistenceProvider::Transactions & transactions()
    { return m_persistence_provider->transactions(); }

    void add_account(const Account & account);

    void add_transaction(
            double sum,
            int account_id,
            const QDate & date,
            const QTime & time);

private:
    std::unique_ptr<IPersistenceProvider> m_persistence_provider;
};

} //namespace MyFinance

#endif // DATABASEMANAGER_H
