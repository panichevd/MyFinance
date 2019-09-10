#ifndef IPERSISTENCEPROVIDER_H
#define IPERSISTENCEPROVIDER_H

#include <QObject>
#include <QSqlTableModel>

#include <memory>

#include "Account.h"

class IPersistenceProvider : public QObject
{
    Q_OBJECT

public:
    IPersistenceProvider() = default;
    virtual ~IPersistenceProvider() = default;

    virtual bool read_data() = 0;

    virtual QSqlTableModel* & model() = 0;
};

#endif // IPERSISTENCEPROVIDER_H
