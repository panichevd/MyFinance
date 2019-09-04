#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Account.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_db_manager()
{
    ui->setupUi(this);

    new_transaction_action = new QAction("New Transcation");
    connect(new_transaction_action, &QAction::triggered, this, &MainWindow::new_transaction_slot);

    auto transactions = ui->menuBar->addMenu("Transactions");
    transactions->addAction(new_transaction_action);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_transaction_slot()
{
    Account acc;
    QApplication::quit();
}
