#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "DataBaseManager.h"

namespace MyFinance {

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();  

private slots:
    void on_newAccountButton_clicked();
    void on_newTransactionButton_clicked();

private:
    void setup_accounts();
    void setup_transactions();

private:
    Ui::MainWindow *ui;

private:
    DataBaseManager m_db_manager;
};

} //namespace MyFinance

#endif // MAINWINDOW_H
