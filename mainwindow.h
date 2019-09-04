#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "DataBaseManager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void new_transaction_slot();

private:
    Ui::MainWindow *ui;

    QAction *new_transaction_action = nullptr;

private:
    DataBaseManager m_db_manager;
};

#endif // MAINWINDOW_H
