#include "Account.h"

namespace MyFinance {

Account::Account(const QString & name, double balance) :
    m_name(name),
    m_balance(balance)
{

}

} //namespace MyFinance
