#ifndef POSTGRESQLPERSISTENCEPROVIDER_H
#define POSTGRESQLPERSISTENCEPROVIDER_H

#include <QSqlDatabase>
#include <QSqlError>

#include "IPersistenceProvider.h"

// Well, initially I wanted to use PostgreSQL as DB, but then
// decided that I want the app to be fully local for now.
// But maybe in the future there will be a PostgreSQL cloud DB
// or something, so I let the interface stay here for now


class PostgreSqlPersistenceProvider :
        public IPersistenceProvider
{
public:
    PostgreSqlPersistenceProvider();
    virtual ~PostgreSqlPersistenceProvider();

    virtual bool read_data();

private:
    QSqlDatabase db;
};

#endif // POSTGRESQLPERSISTENCEPROVIDER_H
