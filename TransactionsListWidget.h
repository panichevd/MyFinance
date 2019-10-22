#ifndef TRANSACTIONSLISTWIDGET_H
#define TRANSACTIONSLISTWIDGET_H

#include <QListWidget>

class TransactionsListWidget :
    public QListWidget
{
    Q_OBJECT

public:
    TransactionsListWidget(QWidget *parent = nullptr);
};

#endif // TRANSACTIONSLISTWIDGET_H
