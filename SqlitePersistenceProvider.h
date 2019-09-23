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

    virtual void read_data() override final;

private:
    void read_accounts();
    void read_transactions();

private:
    QSqlDatabase m_db;
};

#endif // SQLITEPERSISTENCEPROVIDER_H
