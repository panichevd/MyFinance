#include "NewAccountDialog.h"
#include "ui_NewAccountDialog.h"

NewAccountDialog::NewAccountDialog(DataBaseManager & dbm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAccountDialog),
    m_dbm(dbm)
{
    ui->setupUi(this);
    // TODO: no question mark
}

NewAccountDialog::~NewAccountDialog()
{
    delete ui;
}

void NewAccountDialog::on_buttonOK_clicked()
{
    auto name = ui->lineEdit->text();
    auto balance = ui->lineEdit_2->text().toInt();

    m_dbm.add_account(Account(name, balance));

    accept();

    // TODO: check name, balance
    // TODO: add validators
}
