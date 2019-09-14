#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "DataBaseManager.h"

// TODO: MVC

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
    void on_newAccount_clicked();

private:
    void setup_accounts();

private:
    Ui::MainWindow *ui;

private:
    DataBaseManager m_db_manager;
};

#endif // MAINWINDOW_H
