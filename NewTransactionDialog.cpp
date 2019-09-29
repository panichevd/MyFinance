#include <QDoubleValidator>

#include "NewTransactionDialog.h"
#include "ui_NewTransactionDialog.h"

namespace MyFinance {

NewTransactionDialog::NewTransactionDialog(
        DataBaseManager & dbm,
        QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint),
    ui(new Ui::NewTransactionDialog),
    m_dbm(dbm)
{
    setWindowTitle("New transaction");

    ui->setupUi(this);

    ui->sumLineEdit->setValidator(
                new QDoubleValidator(ui->sumLineEdit));
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
}

NewTransactionDialog::~NewTransactionDialog()
{
    delete ui;
}

} //namespace MyFinance
