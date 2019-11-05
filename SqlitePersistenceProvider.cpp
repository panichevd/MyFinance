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

    m_accounts_model = new QSqlTableModel(this, m_db);
    m_accounts_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
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
                  "account2_id INTEGER,"
                  "FOREIGN KEY(account_id) REFERENCES accounts(id),"
                  "FOREIGN KEY(account2_id) REFERENCES accounts(id))");
    if (!query.exec()) {
        throw PersistenceException(
                    "Sql Error: "         + query.lastError().text() +
                    ". Executing query: " + query.executedQuery());
    }

    query.prepare("SELECT date FROM transactions ORDER BY date DESC;");
    query.exec();

    while (query.next()) {
        QString date = query.value(0).toString();
        get_transaction_table(date);
    }
}

QSqlRelationalTableModel * SqlitePersistenceProvider::get_transaction_table(
        const QString & date)
{
    QSqlRelationalTableModel *transactions_model = nullptr;
    auto it = m_transactions.find(date);
    if (it == m_transactions.end()) {
        transactions_model = new QSqlRelationalTableModel(this, m_db);
        transactions_model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
        transactions_model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
        transactions_model->setTable("transactions");
        transactions_model->setRelation(2, QSqlRelation("accounts", "id", "name"));
        transactions_model->setHeaderData(2, Qt::Horizontal, "account");
        transactions_model->setRelation(5, QSqlRelation("accounts", "id", "name"));
        transactions_model->setFilter("date=" + ("date('" + date + "')"));
        transactions_model->select();

        m_transactions[date] = transactions_model;
    } else {
        transactions_model = it->second;
    }

    return transactions_model;
}

bool SqlitePersistenceProvider::add_account(
        const QString & name,
        double balance,
        int & id)
{
    QSqlRecord record = m_accounts_model->record();
    record.setGenerated("id", false);
    record.setValue("name", name);
    record.setValue("balance", balance);

    if (!m_accounts_model->insertRecord(-1, record)) {
        return false;
    }

    if (!m_accounts_model->submitAll()) {
        return false;
    }

    id = m_accounts_model->query().lastInsertId().toInt();
    return true;
}

bool SqlitePersistenceProvider::add_transaction(
        double sum,
        int account_id,
        const QDate & date,
        const QTime & time)
{
    const QString & date_string = date.toString("yyyy-MM-dd");

    QSqlRelationalTableModel *transactions_model =
            get_transaction_table(date_string);

    QSqlRecord record = transactions_model->record();
    record.setGenerated("id", false);
    record.setValue("sum", sum);
    record.setValue(2, account_id); // relation
    record.setValue("date", date_string);
    record.setValue("time", time.toString());

    if (!transactions_model->insertRecord(-1, record)) {
        qDebug() << "Failed to insert new transaction:"
                 << transactions_model->lastError();
        return false;
    }

    for (int i = 0; i < m_accounts_model->rowCount(); ++i) {
        QSqlRecord record = m_accounts_model->record(i);
        if (record.value("id").toInt() == account_id) {
            record.setValue("balance", record.value("balance").toDouble() + sum);

            if (!m_accounts_model->setRecord(i, record)) {
                qDebug() << "Failed to modify account balance: "
                         << m_accounts_model->lastError();
                transactions_model->revertAll();
                return false;
            }
        }
    }

    if (!transactions_model->submitAll() || !m_accounts_model->submitAll()) {
        return false;
    }

    emit transactionsTableAdded(date_string, transactions_model);
    return true;
}

bool SqlitePersistenceProvider::add_transfer(
        double sum,
        int account_id,
        int account2_id,
        const QDate & date,
        const QTime & time)
{
    const QString & date_string = date.toString("yyyy-MM-dd");

    QSqlRelationalTableModel *transactions_model =
            get_transaction_table(date_string);

    QSqlRecord record = transactions_model->record();
    record.setGenerated("id", false);
    record.setValue("sum", sum);
    record.setValue(2, account_id); // relation
    record.setValue("date", date_string);
    record.setValue("time", time.toString());
    record.setValue(5, account2_id); // relation

    if (!transactions_model->insertRecord(-1, record)) {
        qDebug() << "Failed to insert new transaction:"
                 << transactions_model->lastError();
        return false;
    }

    for (int i = 0; i < m_accounts_model->rowCount(); ++i) {
        QSqlRecord record = m_accounts_model->record(i);
        if (record.value("id").toInt() == account_id) {
            record.setValue("balance", record.value("balance").toDouble() - sum);

            if (!m_accounts_model->setRecord(i, record)) {
                qDebug() << "Failed to modify account balance: "
                         << m_accounts_model->lastError();
                m_accounts_model->revertAll();
                transactions_model->revertAll();
                return false;
            }
        } else if (record.value("id").toInt() == account2_id) {
            record.setValue("balance", record.value("balance").toDouble() + sum);

            if (!m_accounts_model->setRecord(i, record)) {
                qDebug() << "Failed to modify account balance: "
                         << m_accounts_model->lastError();
                m_accounts_model->revertAll();
                transactions_model->revertAll();
                return false;
            }
        }
    }

    if (!transactions_model->submitAll() || !m_accounts_model->submitAll()) {
        return false;
    }

    emit transactionsTableAdded(date_string, transactions_model);
    return true;
}

} //namespace MyFinance
