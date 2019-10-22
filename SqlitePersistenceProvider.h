#ifndef SQLITEPERSISTENCEPROVIDER_H
#define SQLITEPERSISTENCEPROVIDER_H

#include <QSqlDatabase>

#include "PersistenceProvider.h"

namespace MyFinance {

class SqlitePersistenceProvider :
        public PersistenceProvider
{
public:
    SqlitePersistenceProvider();
    virtual ~SqlitePersistenceProvider();

    virtual void read_data(
            std::map<QString, Account> & accounts)
            override final;

    virtual bool add_account(
            const QString & name,
            double balance,
            int & id) override final;

    virtual bool add_transaction(
            double sum,
            int account_id,
            const QDate & date,
            const QTime & time) override final;

    virtual bool add_transfer(
            double sum,
            int account_id,
            int account2_id,
            const QDate & date,
            const QTime & time) override final;

private:
    void read_accounts(std::map<QString, Account> & accounts);
    void read_transactions();

    QSqlRelationalTableModel * get_transaction_table(const QString & date);

private:
    QSqlDatabase m_db;
};

} //namespace MyFinance

#endif // SQLITEPERSISTENCEPROVIDER_H
