#ifndef SQLITEPERSISTENCEPROVIDER_H
#define SQLITEPERSISTENCEPROVIDER_H

#include <QSqlDatabase>

#include "IPersistenceProvider.h"

class SqlitePersistenceProvider :
        public IPersistenceProvider
{
public:
    SqlitePersistenceProvider();
    virtual ~SqlitePersistenceProvider();

    virtual bool read_data();

private:
    QSqlDatabase db;
};

#endif // SQLITEPERSISTENCEPROVIDER_H
