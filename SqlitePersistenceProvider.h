#ifndef SQLITEPERSISTENCEPROVIDER_H
#define SQLITEPERSISTENCEPROVIDER_H

#include <QSqlDatabase>

#include "PersistenceProvider.h"

class SqlitePersistenceProvider :
        public PersistenceProvider
{
public:
    SqlitePersistenceProvider();
    virtual ~SqlitePersistenceProvider();

    virtual bool read_data();

private:
    QSqlDatabase db;
};

#endif // SQLITEPERSISTENCEPROVIDER_H
