#include "SqlitePersistenceProvider.h"

#include <QDate>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QStringList>
#include <QTime>

namespace MyFinance {

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

void SqlitePersistenceProvider::read_data(
        std::map<QString, Account> & accounts)
{
    read_accounts(accounts);
    read_transactions();
}

void SqlitePersistenceProvider::read_accounts(
        std::map<QString, Account> & accounts)
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

    query.prepare("SELECT * FROM accounts");
    query.exec();
    while (query.next()) {
        int id         = query.value(0).toInt();
        QString name   = query.value(1).toString();
        double balance = query.value(2).toDouble();

        accounts[name] = Account(id, name, balance);
    }
}

void SqlitePersistenceProvider::read_transactions()
{
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS transactions("
                  "id INTEGER PRIMARY KEY, "
                  "sum REAL NOT NULL,"
                  "account_id INTEGER NOT NULL,"
                  "date TEXT NOT NULL,"
                  "time TEXT NOT NULL,"
                  "FOREIGN KEY(account_id) REFERENCES accounts(id))");
    if (!query.exec()) {
        throw PersistenceException(
                    "Sql Error: "         + query.lastError().text() +
                    ". Executing query: " + query.executedQuery());
    }

    query.prepare("SELECT date FROM transactions ORDER BY date DESC;");
    query.exec();

    while (query.next()) {
        QString date = query.value(0).toString();

        QSqlRelationalTableModel *transactions_model = new QSqlRelationalTableModel(this, m_db);
        transactions_model->setTable("transactions");
        transactions_model->setRelation(2, QSqlRelation("accounts", "id", "name"));
        transactions_model->setFilter("date=" + ("date('" + date + "')"));
        transactions_model->select();

        m_transactions[date] = transactions_model;
    }

    /*for (int i = 1; i < 20; ++ i) {
        query.prepare("INSERT INTO transactions (sum, account_id, date, time) VALUES(" + QString::number(300) + ", 1, date('" + QString::number(2010 + i) + "-10-16'), time('now'));");
        query.exec();
        qDebug() << "Sql Error: "         + query.lastError().text() +
                    ". Executing query: " + query.executedQuery();
    }*/
}

void SqlitePersistenceProvider::add_transaction(
        double sum,
        int account_id,
        const QDate & date,
        const QTime & time)
{
    QSqlQuery query;

    query.prepare("INSERT INTO transactions (sum, account_id, date, time) "
                  "VALUES(" +
                      QString::number(sum) + ", " +
                      QString::number(account_id) + ", "
                      "date('" + date.toString("yyyy-MM-dd") + "'), "
                      "time('" + time.toString() + "'));");
    query.exec();

    // TODO: update m_transactions
}

} //namespace MyFinance
