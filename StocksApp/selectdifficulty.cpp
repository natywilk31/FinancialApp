/// This is the implementation file for the select difficulty dialog of our app,
/// which allows the user to choose easy, medium, or hard.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "selectdifficulty.h"
#include "ui_selectdifficulty.h"

SelectDifficulty::SelectDifficulty(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SelectDifficulty)
{
    gameHome = new GameHome();
    ui->setupUi(this);

    // connect the clicked signal of easy, medium, hard to our slots for each button
    connect(ui->easy, &QPushButton::clicked, this, &SelectDifficulty::easyPushed);
    connect(ui->medium, &QPushButton::clicked, this, &SelectDifficulty::mediumPushed);
    connect(ui->hard, &QPushButton::clicked, this, &SelectDifficulty::hardPushed);
    connect(this, &SelectDifficulty::difficultySelected, gameHome, &GameHome::setUpGame);
}

SelectDifficulty::~SelectDifficulty()
{
    delete ui;
}

/// hide the current window, open up the home screen, and emit that the difficulty level is 1
void SelectDifficulty::easyPushed()
{
    this->hide();
    emit difficultySelected(1);
    gameHome->exec();
}

/// hide the current window, open up the home screen, and emit that the difficulty level is 2
void SelectDifficulty::mediumPushed()
{
    this->hide();
    emit difficultySelected(2);
    gameHome->exec();
}

/// hide the current window, open up the home screen, and emit that the difficulty level is 3
void SelectDifficulty::hardPushed()
{
    this->hide();
    emit difficultySelected(3);
    gameHome->exec();
}
