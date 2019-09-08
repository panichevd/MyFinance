#ifndef PERSISTENCEPROVIDER_H
#define PERSISTENCEPROVIDER_H

#include "IPersistenceProvider.h"

class PersistenceProvider :
        public IPersistenceProvider
{
public:
    PersistenceProvider() = default;
    virtual ~PersistenceProvider() = default;

    virtual const QVector<Account> & accounts() const noexcept
    { return m_accounts; }

protected:
    // TODO: shared_ptr ?
    QVector<Account> m_accounts;
};

#endif // PERSISTENCEPROVIDER_H
