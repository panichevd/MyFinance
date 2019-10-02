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
            int account_id,
            const QDate & date,
            const QTime & time,
            int account_id2 = 0) = 0;
};

namespace {

class TransactionStateIncome :
    public TransactionState
{
public:
    virtual bool add(
            DataBaseManager & dbm,
            double sum,
            int account_id,
            const QDate & date,
            const QTime & time,
            int account_id2 = 0) override
    {
        Q_ASSERT(account_id2 == 0);
        dbm.add_transaction(sum, account_id, date, time);
        return true;
    }
};

class TransactionStateExpense :
    public TransactionState
{
public:
    virtual bool add(
            DataBaseManager & dbm,
            double sum,
            int account_id,
            const QDate & date,
            const QTime & time,
            int account_id2 = 0) override
    {
        Q_ASSERT(account_id2 == 0);
        dbm.add_transaction(-sum, account_id, date, time);
        return true;
    }
};

class TransactionStateTransfer :
    public TransactionState
{
public:
    virtual bool add(
            DataBaseManager & dbm,
            double sum,
            int account_id,
            const QDate & date,
            const QTime & time,
            int account_id2 = 0) override
    {
        if (account_id2 == 0) {
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
    auto sum         = ui->sumLineEdit->text().toDouble();
    auto account_id  = ui->accountLineEdit->text().toInt(); // TODO: lookup by name
    auto account_id2 = ui->account2Edit->text().toInt();
    auto date        = ui->dateEdit->date();
    auto time        = ui->timeEdit->time();

    if (m_current_state->add(m_dbm, sum, account_id, date, time, account_id2)) {
        QDialog::accept();
    }
}

} //namespace MyFinance
