#include "NewTransactionDialog.h"
#include "ui_NewTransactionDialog.h"

NewTransactionDialog::NewTransactionDialog(DataBaseManager & dbm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTransactionDialog),
    m_dbm(dbm)
{
    ui->setupUi(this);
    // TODO: no question mark
}

NewTransactionDialog::~NewTransactionDialog()
{
    delete ui;
}
