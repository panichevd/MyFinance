#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

namespace MyFinance {

class Account
{
public:
    Account(const QString & name, double balance);

    QString name() const
    { return m_name; }
    void set_name(const QString &name)
    { m_name = name; }

    double balance() const
    { return m_balance; }
    void set_balance(double balance)
    { m_balance = balance; }

private:
    QString m_name;
    double m_balance;
    //TODO: Ccy
};

} //namespace MyFinance

#endif // ACCOUNT_H
