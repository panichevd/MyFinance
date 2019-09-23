#include "TransactionsModel.h"

TransactionItem::TransactionItem(TransactionItem *parent)
{
}

TransactionItem * TransactionItem::child(int row)
{
    return nullptr;
}

TransactionsModel::TransactionsModel(QObject * parent):
    QAbstractItemModel(parent)
{
}
