#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account
{
public:
    Account(const QString & name, int balance);

    QString name() const
    { return m_name; }
    void set_name(const QString &name)
    { m_name = name; }

    int balance() const
    { return m_balance; }
    void set_balance(int balance)
    { m_balance = balance; }

private:
    QString m_name;
    int m_balance;
    //TODO: Ccy
};

#endif // ACCOUNT_H
