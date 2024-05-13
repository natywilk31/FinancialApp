#include "transfermoneydialog.h"
#include "ui_transfermoneydialog.h"

transferMoneyDialog::transferMoneyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transferMoneyDialog)
{
    ui->setupUi(this);

    //connect(ui->transferButton, &QPushButton::clicked, GameHome, &Model::transferMoney);
}

transferMoneyDialog::~transferMoneyDialog()
{
    delete ui;
}

void transferMoneyDialog::on_transferButton_clicked()
{
    double amount = ui->amountSpinBox->value();
    QString sendingAccount = ui->fromComboBox->currentText();
    QString receivingAccount = ui->toComboBox->currentText();

    emit transfer(amount, sendingAccount, receivingAccount);
    accept();
}

