/// This is the implementation file for each confetti piece.
/// It uses box2d to simulate gravity.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "confettipiece.h"
#include "Box2D/Dynamics/b2World.h"
#include "qcolor.h"

confettiPiece::confettiPiece(qreal x, qreal y, qreal ang, QColor col)
    : world(*new b2Vec2(0.0f, 3.0f))
{
    // save color and angle to use later
    this->col = col;
    this->ang = ang;

    // box2d stuff
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    body = world.CreateBody(&bodyDef);
}

