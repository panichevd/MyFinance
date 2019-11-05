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

public slots:
    void onTransactionsTableAdded(
            const QString & date,
            QSqlRelationalTableModel * transactions);

private:
    typedef std::map<
        QString,
        QListWidgetItem*,
        std::greater<QString>> Transactions;

private:
    QFont m_font;
    int m_row_height = 0;

    Transactions m_transactions;
};

#endif // TRANSACTIONSLISTWIDGET_H
