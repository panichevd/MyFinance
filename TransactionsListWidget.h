#ifndef TRANSACTIONSLISTWIDGET_H
#define TRANSACTIONSLISTWIDGET_H

#include <QListWidget>

#include "DataBaseManager.h"

class TransactionsListWidget :
    public QListWidget
{
    Q_OBJECT

public:
    TransactionsListWidget(QWidget *parent = nullptr);

    void setup_transactions(MyFinance::DataBaseManager & dbm);

private:
    QFont m_font;
};

#endif // TRANSACTIONSLISTWIDGET_H
