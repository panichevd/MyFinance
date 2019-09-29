#include <QDoubleValidator>

#include "NewAccountDialog.h"
#include "ui_NewAccountDialog.h"

namespace MyFinance {

NewAccountDialog::NewAccountDialog(DataBaseManager & dbm, QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint),
    ui(new Ui::NewAccountDialog),
    m_dbm(dbm)
{
    setWindowTitle("New account");

    ui->setupUi(this);

    ui->balanceLineEdit->setValidator(
                new QDoubleValidator(ui->balanceLineEdit));
}

NewAccountDialog::~NewAccountDialog()
{
    delete ui;
}

void NewAccountDialog::on_buttonOK_clicked()
{
    auto name = ui->nameLineEdit->text();
    auto balance = ui->balanceLineEdit->text().toDouble();

    m_dbm.add_account(Account(name, balance));

    accept();
}

} //namespace MyFinance
