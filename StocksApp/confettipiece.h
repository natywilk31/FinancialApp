/// This is the header file for a singular piece of confetti.
/// It has Box2D properties.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef CONFETTIPIECE_H
#define CONFETTIPIECE_H

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "qcolor.h"
#include "qtypes.h"

class confettiPiece
{
public:
    // want to get initial position, angle to tilt at, and color. each is chosen randomly in the celebrationScreen
    confettiPiece(qreal x, qreal y, qreal ang, QColor col);

    // things for box2d
    b2Body* body;
    b2World world;

    // store the constructor inputs for later
    qreal ang;
    QColor col;

private:
    // box2d stuff
    b2BodyDef groundBodyDef;
    b2Body* groundBody;
    b2PolygonShape groundBox;
    b2BodyDef bodyDef;
    b2PolygonShape dynamicBox;
    b2FixtureDef fixtureDef;
};

#endif // CONFETTIPIECE_H
