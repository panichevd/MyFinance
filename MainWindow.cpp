#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "Account.h"
#include "NewAccountDialog.h"

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

    auto accounts_view =
                accounts_tab->findChild<QTableView*>(
                    QString("accountsView"),
                    Qt::FindChildrenRecursively);
    accounts_view->setModel(m_db_manager.accounts_model());
    accounts_view->setEditTriggers(QTableView::NoEditTriggers);
    accounts_view->setColumnHidden(0, true);
    accounts_view->verticalHeader()->setVisible(false);
    accounts_view->show();

    // TODO: open account edit view on account click
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newAccount_clicked()
{
    NewAccountDialog dialog(m_db_manager);
    dialog.exec();
}
