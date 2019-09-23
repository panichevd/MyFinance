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
        throw PersistenceException("No sqlite driver available");
    }

    m_db = QSqlDatabase::addDatabase(driver);
    m_db.setDatabaseName("finance");

    if (!m_db.open()) {
        throw PersistenceException(
                    "Could not open data base. Error: " +
                    m_db.lastError().text());
    }

    m_accounts_model = new QSqlTableModel(this, m_db);
}

SqlitePersistenceProvider::~SqlitePersistenceProvider()
{
    m_db.close();
}

void SqlitePersistenceProvider::read_data()
{
    read_accounts();
    read_transactions();
}

void SqlitePersistenceProvider::read_accounts()
{    
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS accounts("
                  "id INTEGER PRIMARY KEY, "
                  "name TEXT NOT NULL, "
                  "balance REAL NOT NULL)");
    if (!query.exec()) {
        throw PersistenceException(
                    "Sql Error: "         + query.lastError().text() +
                    ". Executing query: " + query.executedQuery());
    }

    m_accounts_model->setTable("accounts");
    m_accounts_model->select();
}

void SqlitePersistenceProvider::read_transactions()
{
    // TODO: split date and time
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS transactions("
                  "id INTEGER PRIMARY KEY, "
                  "sum REAL NOT NULL,"
                  "account_id INTEGER NOT NULL,"
                  "datetime TEXT NOT NULL,"
                  "FOREIGN KEY(account_id) REFERENCES accounts(id))");
    if (!query.exec()) {
        throw PersistenceException(
                    "Sql Error: "         + query.lastError().text() +
                    ". Executing query: " + query.executedQuery());
    }

    query.prepare("SELECT datetime FROM transactions;");
    query.exec();

    while (query.next()) {
        // TODO: methods field names
        QString date = query.value(0).toString();

        QSqlTableModel *transactions_model = new QSqlTableModel(this, m_db);
        transactions_model->setTable("transactions");
        transactions_model->setFilter("datetime=" + date);
        transactions_model->select();

        m_transactions[date] = transactions_model;
    }

    /*query.prepare("INSERT INTO transactions (id, sum, account_id, datetime) VALUES(2, 300, 1, 'f');");
    query.exec();
    qDebug() << "Sql Error: "         + query.lastError().text() +
                ". Executing query: " + query.executedQuery();*/
}
