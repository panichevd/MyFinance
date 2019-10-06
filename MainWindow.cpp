#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "NewAccountDialog.h"
#include "NewTransactionDialog.h"

#include <QDebug>

#include <QLabel>
#include <QScrollArea>
#include <QTabWidget>
#include <QTableView>
#include <QPushButton>

namespace MyFinance {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_db_manager()
{
    ui->setupUi(this);

    setup_accounts();
    setup_transactions();

    // TODO: db_manager as pointer. Catch exception
}

void MainWindow::setup_accounts()
{
    // TODO: error handling
    auto accounts_view = ui->accountsView;
    accounts_view->setModel(m_db_manager.accounts_model());
    accounts_view->setEditTriggers(QTableView::NoEditTriggers);
    accounts_view->setColumnHidden(0, true);
    accounts_view->verticalHeader()->setVisible(false);
    accounts_view->show();

    // TODO: open account edit view on account click
}

// TODO: inherit from QListWiedget
void MainWindow::setup_transactions()
{
    // TODO: QFont, then calculate size based on date item size
    // TODO: Borders
    auto transactions_list = ui->listWidget;

    QFont font("Segoe UI");
    font.setPointSize(9);

    const auto & transactions = m_db_manager.transactions();
    for (const auto & transaction : transactions) {
        QListWidgetItem * item = new QListWidgetItem;
        item->setFont(font);

        auto label = new QLabel(transaction.first, this);
        label->setFont(font);

        item->setFont(font);
        transactions_list->addItem(item);
        transactions_list->setItemWidget(item, label);

        QTableView * view = new QTableView(this);
        view->setModel(transaction.second);
        view->setColumnHidden(0, true);
        view->verticalHeader()->setVisible(false);
        view->setFont(font);

        QListWidgetItem * item2 = new QListWidgetItem;

        item2->setSizeHint(QSize(200, 4*label->sizeHint().height()));
        transactions_list->addItem(item2);
        transactions_list->setItemWidget(item2, view);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newAccountButton_clicked()
{
    NewAccountDialog dialog(m_db_manager);
    dialog.exec();
}

void MainWindow::on_newTransactionButton_clicked()
{
    NewTransactionDialog dialog(m_db_manager);
    dialog.exec();
}

} //namespace MyFinance
