#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <memory>

#include "Account.h"
#include "IPersistenceProvider.h"

namespace MyFinance {

class DataBaseManager :
        public QObject
{
    Q_OBJECT

public:
    DataBaseManager();
    ~DataBaseManager() = default;

    QSqlTableModel* & accounts_model()
    { return m_persistence_provider->model(); }

    IPersistenceProvider::Transactions & transactions()
    { return m_persistence_provider->transactions(); }

    void add_account(
            const QString & name,
            double balance);

    bool add_transaction(
            double sum,
            const QString & account_name,
            const QDate & date,
            const QTime & time);

    bool add_transfer(
            double sum,
            const QString & account_name,
            const QString & account2_name,
            const QDate & date,
            const QTime & time);

signals:
    void transactionsTableAdded(
            const QString & date,
            QSqlRelationalTableModel * transactions);

private:
    std::unique_ptr<IPersistenceProvider> m_persistence_provider;

    std::map<QString, Account> m_accounts;
};

} //namespace MyFinance

#endif // DATABASEMANAGER_H
