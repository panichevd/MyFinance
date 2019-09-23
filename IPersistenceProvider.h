#ifndef IPERSISTENCEPROVIDER_H
#define IPERSISTENCEPROVIDER_H

#include <QException>
#include <QObject>
#include <QSqlTableModel>

#include <memory>

#include "Account.h"

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
    typedef std::map<QString, QSqlTableModel*> Transactions;

public:
    IPersistenceProvider() = default;
    virtual ~IPersistenceProvider() = default;

    virtual void read_data() = 0;

    virtual QSqlTableModel* & model() = 0;
    virtual Transactions    & transactions() = 0;
};

#endif // IPERSISTENCEPROVIDER_H
