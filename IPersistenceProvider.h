#ifndef IPERSISTENCEPROVIDER_H
#define IPERSISTENCEPROVIDER_H

// TODO: this is supposed to be just an interface!

#include <QVector>

#include <memory>

#include "Account.h"

class IPersistenceProvider
{
public:
    IPersistenceProvider() = default;
    virtual ~IPersistenceProvider() = default;

    virtual bool read_data() = 0;

    virtual const QVector<Account> & accounts() const noexcept = 0;
};

#endif // IPERSISTENCEPROVIDER_H
