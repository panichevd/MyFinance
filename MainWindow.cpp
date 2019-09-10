#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Account.h"

#include <QTabWidget>
#include <QTableView>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_db_manager()
{
    ui->setupUi(this);

    setup_accounts();
}

void MainWindow::setup_accounts()
{
    // TODO: error handling
    auto accounts_tab = ui->tabWidget->widget(0);

    auto new_account_button =
            accounts_tab->findChild<QPushButton*>(
                QString("newAccount"),
                Qt::FindChildrenRecursively);
    connect(new_account_button, SIGNAL(pressed()), this, SLOT(new_account_slot()));

    auto accounts_view =
                accounts_tab->findChild<QTableView*>(
                    QString("accountsView"),
                    Qt::FindChildrenRecursively);
    accounts_view->setModel(m_db_manager.accounts_model());
    accounts_view->show();

    // TODO: some action on account click
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_account_slot()
{
    // TODO: show new account form
}
