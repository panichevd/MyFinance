#include <QHeaderView>
#include <QLabel>
#include <QDebug>
#include <QTableView>

#include "DataBaseManager.h"
#include "TransactionsListWidget.h"

// TODO: sort views
TransactionsListWidget::TransactionsListWidget(QWidget * parent) :
    QListWidget(parent),
    m_font("Segoe UI")
{
    m_font.setPointSize(12);

    auto label = new QLabel("", this);
    label->setFont(m_font);
    m_row_height = label->sizeHint().height();
}

void TransactionsListWidget::setup_transactions(
        MyFinance::DataBaseManager & dbm)
{
    const auto & transactions = dbm.transactions();
    for (const auto & transaction : transactions) {
        onTransactionsTableAdded(transaction.first, transaction.second);
    }
}

void TransactionsListWidget::onTransactionsTableAdded(
        const QString & date,
        QSqlRelationalTableModel * transactions)
{
    auto it = m_transactions.find(date);
    if (it == m_transactions.end()) {
        // Date as table header
        auto label = new QLabel(date, this);
        label->setFont(m_font);

        QListWidgetItem * item = new QListWidgetItem;
        item->setFont(m_font);
        this->addItem(item);
        this->setItemWidget(item, label);

        // Transactions table
        QTableView * view = new QTableView(this);
        view->setModel(transactions);
        view->setColumnHidden(0, true);
        view->verticalHeader()->setVisible(false);
        view->verticalHeader()->setFont(m_font);
        view->setFont(m_font);

        QListWidgetItem * item2 = new QListWidgetItem;
        this->addItem(item2);
        this->setItemWidget(item2, view);

        it = m_transactions.insert(std::make_pair(date, item2)).first;
    }

    auto row_count = transactions->rowCount();
    it->second->setSizeHint(QSize(200, (row_count + 1)*(1.5)*m_row_height)); // Based on 12. TODO: better calculation
}
