#ifndef NEWACCOUNTDIALOG_H
#define NEWACCOUNTDIALOG_H

#include <QDialog>

#include "DataBaseManager.h"

namespace MyFinance {

namespace Ui {
class NewAccountDialog;
}

class NewAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAccountDialog(DataBaseManager & dbm, QWidget *parent = 0);
    ~NewAccountDialog();

private slots:
    virtual void accept() override;

private:
    Ui::NewAccountDialog *ui;

    DataBaseManager & m_dbm;
};

#endif // NEWACCOUNTDIALOG_H

} //namespace MyFinance
