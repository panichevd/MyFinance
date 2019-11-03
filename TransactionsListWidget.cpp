#include <QHeaderView>
#include <QLabel>
#include <QDebug>
#include <QTableView>

#include "DataBaseManager.h"
#include "TransactionsListWidget.h"

TransactionsListWidget::TransactionsListWidget(QWidget * parent) :
    QListWidget(parent),
    m_font("Segoe UI")
{
    m_font.setPointSize(12);
}

void TransactionsListWidget::setup_transactions(
        MyFinance::DataBaseManager & dbm)
{
    const auto & transactions = dbm.transactions();
    for (const auto & transaction : transactions) {
        QListWidgetItem * item = new QListWidgetItem;
        item->setFont(m_font);

        auto label = new QLabel(transaction.first, this);
        label->setFont(m_font);

        item->setFont(m_font);
        this->addItem(item);
        this->setItemWidget(item, label);

        QTableView * view = new QTableView(this);
        view->setModel(transaction.second);
        view->setColumnHidden(0, true);
        view->verticalHeader()->setVisible(false);
        view->verticalHeader()->setFont(m_font);
        view->setFont(m_font);

        QListWidgetItem * item2 = new QListWidgetItem;

        auto row_count = transaction.second->rowCount();
        item2->setSizeHint(QSize(200, (row_count + 1)*(1.5)*label->sizeHint().height())); // Based on 12. TODO: better calculation?
        this->addItem(item2);
        this->setItemWidget(item2, view);
    }
}
