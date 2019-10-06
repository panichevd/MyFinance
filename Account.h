#ifndef ACCOUNT_H
#define ACCOUNT_H

namespace MyFinance {

class Account
{
public:
    Account () = default;

    Account(int id, const QString & name, double balance) :
        m_id(id),
        m_name(name),
        m_balance(balance)
    { }

    int id() const
    { return m_id; }

    QString name() const
    { return m_name; }

    double balance() const
    { return m_balance; }

private:
    int     m_id;
    QString m_name;
    double m_balance;
    //TODO: Ccy
};

} //namespace MyFinance

#endif // ACCOUNT_H
