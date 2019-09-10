#ifndef PERSISTENCEPROVIDER_H
#define PERSISTENCEPROVIDER_H

#include "IPersistenceProvider.h"

class PersistenceProvider :
        public IPersistenceProvider
{
public:
    PersistenceProvider() = default;
    virtual ~PersistenceProvider() = default;

    virtual QSqlTableModel* & model()
    { return m_accounts_model; }

protected:
    QSqlTableModel *m_accounts_model = nullptr;
};

#endif // PERSISTENCEPROVIDER_H
