#include "PostgreSqlPersistenceProvider.h"

PostgreSqlPersistenceProvider::PostgreSqlPersistenceProvider()
{
    static const QString driver = "QPSQL";

    if (!QSqlDatabase::isDriverAvailable(driver)) {
        // TODO: throw exception
        return;
    }
    db = QSqlDatabase::addDatabase(driver);
    db.setHostName("127.0.0.1");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("1234");

    if (!db.open()) {
        // TODO: throw exception
    }
}

PostgreSqlPersistenceProvider::~PostgreSqlPersistenceProvider()
{
    db.close();
}

bool PostgreSqlPersistenceProvider::read_data()
{
    return false;
}
