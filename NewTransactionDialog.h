#ifndef NEWTRANSACTIONDIALOG_H
#define NEWTRANSACTIONDIALOG_H

#include <QDialog>

#include "DataBaseManager.h"

namespace Ui {
class NewTransactionDialog;
}

class NewTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTransactionDialog(DataBaseManager & dbm, QWidget *parent = 0);
    ~NewTransactionDialog();

private:
    Ui::NewTransactionDialog *ui;

    DataBaseManager & m_dbm;
};

#endif // NEWTRANSACTIONDIALOG_H
