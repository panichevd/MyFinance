#include "SqlitePersistenceProvider.h"
#include "Account.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QStringList>

SqlitePersistenceProvider::SqlitePersistenceProvider()
{
    static const QString driver = "QSQLITE";

    if (!QSqlDatabase::isDriverAvailable(driver)) {
        // TODO: throw exception
        return;
    }

    db = QSqlDatabase::addDatabase(driver);
    db.setDatabaseName("finance");

    if (!db.open()) {
        // TODO: throw exception
        return;
    }
}

bool SqlitePersistenceProvider::read_data()
{    
    // TODO: throw exceptions??
    // TODO: move to separate function
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS accounts("
                  "id INTEGER PRIMARY KEY, "
                  "name TEXT NOT NULL, "
                  "balance INTEGER NOT NULL)");
    if (!query.exec()) {
        qDebug() << "Sql Error: " << query.executedQuery() << endl << query.lastError().text() << endl;
        return false;
    }

    if (!query.exec("SELECT * FROM accounts")) {
        qDebug() << "Sql Error: " << query.executedQuery() << endl << query.lastError().text() << endl;
        return false;
    }

    int idx_id      = query.record().indexOf("id");
    int idx_name    = query.record().indexOf("name");
    int idx_balance = query.record().indexOf("balance");
    while (query.next()) {
        m_accounts.push_back(
                    Account(
                        query.value(idx_id).toInt(),
                        query.value(idx_name).toString(),
                        query.value(idx_balance).toInt()
                    ));
    }

    return true;
}

SqlitePersistenceProvider::~SqlitePersistenceProvider()
{
    db.close();
}
