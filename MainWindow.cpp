#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Account.h"

#include <QTabWidget>
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

    auto accounts_list =
            accounts_tab->findChild<QListWidget*>(
                QString("accountsList"),
                Qt::FindChildrenRecursively);
    for (const auto & account : m_db_manager.accounts()) {
        accounts_list->addItem(account.m_name);
    }

    // TODO: some action on account click
    // TODO: change QListWidget to QTableWidget (for now), then use MVC (later)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_account_slot()
{
    // TODO: show new account form
}
