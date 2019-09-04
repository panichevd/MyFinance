#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account
{
public:
    Account();

private:
    QString m_name;
    int m_balance;
    //TODO: Ccy
    //TODO: date created
};

#endif // ACCOUNT_H
