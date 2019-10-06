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

    virtual void add_transaction(
            double sum,
            int account_id,
            const QDate & date,
            const QTime & time) override final;

private:
    void read_accounts(std::map<QString, Account> & accounts);
    void read_transactions();

private:
    QSqlDatabase m_db;
};

} //namespace MyFinance

#endif // SQLITEPERSISTENCEPROVIDER_H
