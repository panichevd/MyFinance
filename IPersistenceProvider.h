#ifndef IPERSISTENCEPROVIDER_H
#define IPERSISTENCEPROVIDER_H

#include <QException>
#include <QObject>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>

#include <memory>

#include "Account.h"

namespace MyFinance {

class PersistenceException : public QException
{
public:
    PersistenceException(const QString & what) :
        m_what(what)
    { }
    virtual ~PersistenceException() = default;

    virtual PersistenceException* clone() const override
    { return new PersistenceException(m_what); }

    virtual void raise() const override
    { throw *this; }

public:
    virtual const char * what() const noexcept
    { return m_what.toStdString().c_str(); }

private:
    const QString m_what;
};

class IPersistenceProvider : public QObject
{
    Q_OBJECT

public:
    typedef std::map<
        QString,
        QSqlRelationalTableModel*,
        std::greater<QString>> Transactions;

public:
    IPersistenceProvider() = default;
    virtual ~IPersistenceProvider() = default;

    virtual void read_data(std::map<QString, Account> & accounts) = 0;

    virtual QSqlTableModel* & model() = 0;
    virtual Transactions    & transactions() = 0;

    virtual bool add_account(
            const QString & name,
            double balance,
            int & id) = 0;

    virtual bool add_transaction(
            double sum,
            int account_id,
            const QDate & date,
            const QTime & time) = 0;

    virtual bool add_transfer(
            double sum,
            int account_id,
            int account2_id,
            const QDate & date,
            const QTime & time) = 0;
};

} //namespace MyFinance

#endif // IPERSISTENCEPROVIDER_H
