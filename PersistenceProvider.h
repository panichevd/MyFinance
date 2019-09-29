#ifndef PERSISTENCEPROVIDER_H
#define PERSISTENCEPROVIDER_H

#include "IPersistenceProvider.h"
#include "TransactionsModel.h"

namespace MyFinance {

class PersistenceProvider :
        public IPersistenceProvider
{
public:
    PersistenceProvider() = default;
    virtual ~PersistenceProvider() = default;

    virtual QSqlTableModel* & model() override
    { return m_accounts_model; }

    virtual Transactions & transactions() override
    { return m_transactions; }

protected:
    QSqlTableModel *m_accounts_model     = nullptr;

    Transactions m_transactions;
};

} //namespace MyFinance

#endif // PERSISTENCEPROVIDER_H
