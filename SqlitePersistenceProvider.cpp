#include "SqlitePersistenceProvider.h"
#include "Account.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QStringList>

SqlitePersistenceProvider::SqlitePersistenceProvider() :
    PersistenceProvider()
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

    m_accounts_model = new QSqlTableModel(this, db);
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

    m_accounts_model->setTable("accounts");
    m_accounts_model->select();

    return true;
}

SqlitePersistenceProvider::~SqlitePersistenceProvider()
{
    db.close();
}
