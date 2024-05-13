/// This is the header file for the select difficulty dialog of our app,
/// which allows the user to choose easy, medium, or hard.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef SelectDifficulty_H
#define SelectDifficulty_H

#include <QDialog>
#include "gamehome.h"

namespace Ui
{
class SelectDifficulty;
}

class SelectDifficulty : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDifficulty(QWidget *parent = nullptr);
    ~SelectDifficulty();
    // it owns the gamehome, which will pop up after the difficulty is selected. from there the gamehome will take over.
    GameHome * gameHome;


public slots:
    // slots so we can deal with the user input of difficulty
    void easyPushed();
    void mediumPushed();
    void hardPushed();

signals:
    // send out the selected difficulty
    void difficultySelected(int difficulty);

private:
    Ui::SelectDifficulty * ui;
};

#endif // SelectDifficulty_H
