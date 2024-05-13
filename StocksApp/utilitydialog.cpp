/// This is the implementation file for the utility dialog of our app,
/// which we use to display messages to the user.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "utilitydialog.h"
#include "ui_utilitydialog.h"

// just a simple dialog box
utilityDialog::utilityDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::utilityDialog)
{
    ui->setupUi(this);
}

utilityDialog::~utilityDialog()
{
    delete ui;
}
