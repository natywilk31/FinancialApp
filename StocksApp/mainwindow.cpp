/// This is the implementation file for the main window of our app,
/// which allows the user to choose to load a saved game or start a new game.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "selectdifficulty.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->welcomeLabel->setStyleSheet("color: green;");
    ui->welcomeLabel->setFont(QFont("Rockwell", 72));
    // connect the new game button to open the difficulty selection dialog
    connect(ui->newGame, &QPushButton::clicked, this, &MainWindow::displayDifficultySelection);

    int windowWidth = width();
    QPropertyAnimation *titleAnimation = new QPropertyAnimation(ui->welcomeLabel, "pos", this);
    titleAnimation->setDuration(9000);
    titleAnimation->setStartValue(QPoint(-ui->welcomeLabel->width(), ui->welcomeLabel->pos().y()));
    titleAnimation->setEndValue(QPoint(windowWidth, ui->welcomeLabel->pos().y()));

    connect(titleAnimation, &QPropertyAnimation::finished, this, [=]() {
        ui->welcomeLabel->move(-ui->welcomeLabel->width(), ui->welcomeLabel->pos().y());
        titleAnimation->start();
    });

    // Start the animation
    titleAnimation->start();
}



MainWindow::~MainWindow()
{
    delete ui;
}

/// show the difficulty selection dialog
void MainWindow::displayDifficultySelection()
{
    hide();
    difficultSelection.exec();
}
