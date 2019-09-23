#ifndef TRANSACTIONSMODEL_H
#define TRANSACTIONSMODEL_H

#include <QAbstractItemModel>

class TransactionItem
{
public:
    explicit TransactionItem(TransactionItem * parent = nullptr);
    ~TransactionItem() = default;

    TransactionItem * child(int row);
};

class TransactionsModel :
        public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TransactionsModel(QObject * parent = nullptr);

    QVariant data(const QModelIndex & index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex & child) const override;
    int rowCount   (const QModelIndex & parent = QModelIndex()) const override;
    int columnCount(const QModelIndex & parent = QModelIndex()) const override;
};

#endif // TRANSACTIONSMODEL_H
