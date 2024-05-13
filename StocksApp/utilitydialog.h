/// This is the header file for the utility dialog of our app,
/// which we use to display messages to the user.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef UTILITYDIALOG_H
#define UTILITYDIALOG_H

#include <QDialog>

namespace Ui
{
class utilityDialog;
}

class utilityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit utilityDialog(QWidget *parent = nullptr);
    ~utilityDialog();

private:
    Ui::utilityDialog *ui;
};

#endif // UTILITYDIALOG_H
