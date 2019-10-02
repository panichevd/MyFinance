#ifndef NEWTRANSACTIONDIALOG_H
#define NEWTRANSACTIONDIALOG_H

#include <QDialog>

#include "DataBaseManager.h"

namespace MyFinance {

namespace Ui {
class NewTransactionDialog;
}

class TransactionState;

class NewTransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTransactionDialog(DataBaseManager & dbm, QWidget *parent = 0);
    ~NewTransactionDialog();

private slots:
    void on_expenseRadioButton_clicked();
    void on_incomeRadioButton_clicked();
    void on_transferRadioButton_clicked();

    virtual void accept() override;
    \
private:
    Ui::NewTransactionDialog *ui;

    TransactionState * m_current_state = nullptr;

    DataBaseManager & m_dbm;
};

#endif // NEWTRANSACTIONDIALOG_H

} //namespace MyFinance
