#include "SqlitePersistenceProvider.h"

#include <QDebug>
#include <QSqlError>
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
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS accounts(id INTEGER PRIMARY KEY, name TEXT)");
    if (!query.exec()) {
        qDebug() << "Sql Error: " << query.executedQuery() << endl << query.lastError().text() << endl;
        return false;
    }

    // TODO: read accounts

    return true;
}

SqlitePersistenceProvider::~SqlitePersistenceProvider()
{
    db.close();
}
