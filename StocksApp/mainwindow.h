/// This is the header file for the mainwindow of our app.
/// It will give the user the option to open a saved game or create a new game.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "selectdifficulty.h"
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // a member variable of our select difficulty dialog
    SelectDifficulty difficultSelection;

public slots:
    // show the difficulty selection dialog
    void displayDifficultySelection();

private:
    Ui::MainWindow *ui;
    int difficulty;


};
#endif // MAINWINDOW_H
