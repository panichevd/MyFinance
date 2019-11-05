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

// TODO: fonts

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_db_manager(std::make_unique<DataBaseManager>())
{
    ui->setupUi(this);

    setup_accounts();
    setup_transactions();

    QObject::connect(m_db_manager.get(), &DataBaseManager::transactionsTableAdded, ui->listWidget, &TransactionsListWidget::onTransactionsTableAdded);

    // TODO: Catch exception from dbm
}

void MainWindow::setup_accounts()
{
    // TODO: error handling
    auto accounts_view = ui->accountsView;
    accounts_view->setModel(m_db_manager->accounts_model()); // TODO: pass to dbm
    accounts_view->setEditTriggers(QTableView::NoEditTriggers);
    accounts_view->setColumnHidden(0, true);
    accounts_view->verticalHeader()->setVisible(false);
    accounts_view->show();

    // TODO: open account edit view on account click
}

void MainWindow::setup_transactions()
{
    ui->listWidget->setup_transactions(*m_db_manager);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newAccountButton_clicked()
{
    NewAccountDialog dialog(*m_db_manager);
    dialog.exec();
}

void MainWindow::on_newTransactionButton_clicked()
{
    NewTransactionDialog dialog(*m_db_manager);
    dialog.exec();
}

} //namespace MyFinance
