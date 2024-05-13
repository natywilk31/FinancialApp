#ifndef TRANSFERMONEYDIALOG_H
#define TRANSFERMONEYDIALOG_H

#include <QDialog>

namespace Ui {
class transferMoneyDialog;
}

class transferMoneyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit transferMoneyDialog(QWidget *parent = nullptr);
    ~transferMoneyDialog();

private slots:
    void on_transferButton_clicked();

signals:
    void transfer(double amount, QString sendingAccount, QString receivingAccount);

private:
    Ui::transferMoneyDialog *ui;
};

#endif // TRANSFERMONEYDIALOG_H
