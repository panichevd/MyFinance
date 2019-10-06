#include <QDoubleValidator>
#include <QMessageBox>

#include "NewTransactionDialog.h"
#include "ui_NewTransactionDialog.h"

namespace MyFinance {

class TransactionState
{
public:
    virtual bool add(
            DataBaseManager & dbm,
            double sum,
            const QString & account_name,
            const QDate & date,
            const QTime & time,
            const QString & account2_name) = 0;
};

namespace {

class TransactionStateIncome :
    public TransactionState
{
public:
    virtual bool add(
            DataBaseManager & dbm,
            double sum,
            const QString & account_name,
            const QDate & date,
            const QTime & time,
            const QString & account2_name) override
    {
        Q_ASSERT(account2_name.isEmpty());
        return dbm.add_transaction(sum, account_name, date, time);
    }
};

class TransactionStateExpense :
    public TransactionState
{
public:
    virtual bool add(
            DataBaseManager & dbm,
            double sum,
            const QString & account_name,
            const QDate & date,
            const QTime & time,
            const QString & account2_name) override
    {
        Q_ASSERT(account2_name.isEmpty());
        return dbm.add_transaction(-sum, account_name, date, time);
    }
};

class TransactionStateTransfer :
    public TransactionState
{
public:
    virtual bool add(
            DataBaseManager & dbm,
            double sum,
            const QString & account_name,
            const QDate & date,
            const QTime & time,
            const QString & account2_name) override
    {
        if (account2_name.isEmpty()) {
            QMessageBox::information(nullptr, "", "Please enter a valid account id");
            return false;
        }
        // TODO
        return true;
    }
};

TransactionStateIncome   transaction_state_income;
TransactionStateExpense  transaction_state_expense;
TransactionStateTransfer transaction_state_transfer;

}

NewTransactionDialog::NewTransactionDialog(
        DataBaseManager & dbm,
        QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint),
    ui(new Ui::NewTransactionDialog),
    m_current_state(&transaction_state_income),
    m_dbm(dbm)
{
    setWindowTitle("New transaction");

    ui->setupUi(this);

    ui->account2Label->setVisible(false);
    ui->account2Edit->setVisible(false);

    auto sumValidator = new QDoubleValidator(ui->sumLineEdit);
    sumValidator->setBottom(0.0);
    ui->sumLineEdit->setValidator(sumValidator);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
}

NewTransactionDialog::~NewTransactionDialog()
{
    delete ui;
}

void NewTransactionDialog::on_expenseRadioButton_clicked()
{
    ui->account2Label->setVisible(false);
    ui->account2Edit->setVisible(false);

    m_current_state = &transaction_state_income;
}

void NewTransactionDialog::on_incomeRadioButton_clicked()
{
    ui->account2Label->setVisible(false);
    ui->account2Edit->setVisible(false);

    m_current_state = &transaction_state_expense;
}

void NewTransactionDialog::on_transferRadioButton_clicked()
{
    ui->account2Label->setVisible(true);
    ui->account2Edit->setVisible(true);

    m_current_state = &transaction_state_transfer;
}

void NewTransactionDialog::accept()
{
    auto sum            = ui->sumLineEdit->text().toDouble();
    auto account_name   = ui->accountLineEdit->text();
    auto account2_name  = ui->account2Edit->text();
    auto date           = ui->dateEdit->date();
    auto time           = ui->timeEdit->time();

    if (m_current_state->add(m_dbm, sum, account_name, date, time, account2_name)) {
        QDialog::accept();
    }
}

} //namespace MyFinance
