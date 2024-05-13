/// This is the header file for the celebration screen dialog of our app,
/// which exhibits our use of Box2D in our project
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef CELEBRATIONSCREEN_H
#define CELEBRATIONSCREEN_H

#include "confettipiece.h"
#include "qgraphicsscene.h"
#include "qgraphicsview.h"
#include "qrandom.h"
#include "qtimer.h"
#include <QDialog>

namespace Ui
{
class celebrationScreen;
}

class celebrationScreen : public QDialog
{
    Q_OBJECT

public:
    explicit celebrationScreen(QWidget *parent = nullptr);
    ~celebrationScreen();

    // a vector of colors we will be using for confetti pieces
    QVector<QColor> * colors;

private:
    Ui::celebrationScreen *ui;
    // vectors of all the confetti pieces so we can iterate over them
    QVector<confettiPiece*> * particles;

    // the view and scene to draw onto the dialog
    QGraphicsView view;
    QGraphicsScene *scene;

    // timer to step in the box2d world
    QTimer * timer;

    // random object so that we can have many different confetti particles
    QRandomGenerator * rand;

    // the text item "WELL DONE" to be displayed
    QGraphicsTextItem *textItem;

public slots:
    /// receive signal telling us we're allowed to start drawing and stepping
    void updateDrawing();
};

#endif // CELEBRATIONSCREEN_H


