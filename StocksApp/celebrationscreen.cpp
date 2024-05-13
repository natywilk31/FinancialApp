/// This is the implementation class of the celebration screen.
/// It uses a vector of box2d confetti particles to draw a confetti scene to the screen.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "celebrationscreen.h"
#include "qgraphicsitem.h"
#include "qgraphicsscene.h"
#include "ui_celebrationscreen.h"
#include "confettipiece.h"

celebrationScreen::celebrationScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::celebrationScreen)
{
    ui->setupUi(this);

    // Create QGraphicsView and set the scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // initialize the vector for our confetti pieces
    particles = new QVector<confettiPiece*>();

    // initialize timer for stepping through the world
    timer = new QTimer();

    // initialize the random object
    rand = new QRandomGenerator();

    // initialize colors vector and add our 3 colors
    colors = new QVector<QColor>();
    colors->push_back(QColor(Qt::red));
    colors->push_back(QColor(Qt::blue));
    colors->push_back(QColor(Qt::green));

    // ask timer to send signal to update drawing every 10 milliseconds
    connect(timer, &QTimer::timeout, this, &celebrationScreen::updateDrawing);

    // initialize the text item to well done and do some manipulation on it
    QGraphicsTextItem *textItem = new QGraphicsTextItem("WELL\nDONE");
    // Set the font
    QFont font("Arial", 100, QFont::Bold); // Font family, size, and weight
    textItem->setFont(font);
    // Set the position
    textItem->setPos(15, 15); // X and Y coordinates
    // Add the text item to the scene
    scene->addItem(textItem);

    // nested loop to get confetti across the X and Y axes
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            particles->push_back(new confettiPiece(-(60+rand->bounded(3))*i, (60+rand->bounded(3))*j, rand->bounded(15), colors->at(rand->bounded(3))));
            particles->push_back(new confettiPiece(-(60+rand->bounded(3))*i, -(60+rand->bounded(3))*j, rand->bounded(15), colors->at(rand->bounded(3))));
            particles->push_back(new confettiPiece((60+rand->bounded(3))*i, -(60+rand->bounded(3))*j, rand->bounded(15), colors->at(rand->bounded(3))));
            particles->push_back(new confettiPiece((60+rand->bounded(3))*i, (60+rand->bounded(3))*j, rand->bounded(15), colors->at(rand->bounded(3))));

        }
    }
}


celebrationScreen::~celebrationScreen()
{
    delete ui;
    // Free memory allocated for particles
    delete[] particles;
}

void celebrationScreen::updateDrawing()
{
    // we want to do this loop every 10 milliseconds
    timer->start(10);

    float32 timeStep = 1.0f / 60.0f;

    scene->clear(); // Clear the scene before adding new rectangles

    // make sure textItem is set correctly
    QGraphicsTextItem *textItem = new QGraphicsTextItem("WELL\nDONE");
    // Set the font
    QFont font("Arial", 50, QFont::Bold); // Font family, size, and weight
    textItem->setFont(font);
    // Set the position
    textItem->setPos(-100, -100); // X and Y coordinates
    // Add the text item to the scene
    scene->addItem(textItem);

    // iterate over each confetti piece. for each one, get its location a draw a rectangle there.
    // we set the rotation to whatever it is set to in the confetti particle, and do the same with the color.
    for (confettiPiece * c : *particles)
    {
        QGraphicsRectItem *rectItem = scene->addRect(c->body->GetPosition().x, c->body->GetPosition().y, 5, 5, QPen(Qt::black), QBrush(c->col));
        rectItem->setRotation(c->ang);
        c->world.Step(timeStep, 6, 2); // Step the Box2D world once per frame
    }
    ui->graphicsView->update(); // Update the graphics view
}
