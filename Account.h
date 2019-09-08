#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account
{
public:
    Account(int id, const QString & name, int balance);

//private:
    int m_id; // TODO: int??
    QString m_name;
    int m_balance;
    //TODO: Ccy
    //TODO: date created
};

#endif // ACCOUNT_H
