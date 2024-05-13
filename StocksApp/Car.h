/// This is the header file for a car.
/// It has a price and a reliability level. The price is based off of the difficulty the user chooses.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef CAR_H
#define CAR_H

#include <QString>

class Car
{
public:
    // constructors for a basic car, or a car with difficulty and quality
    Car();
    Car(double difficulty, int carQuality, QString name);

    // getter setter for car price
    void setPrice(int);
    int getPrice();
    QString getReliabilityLevel();
    QString name;


    void monthPassed();

private:
    int price;
    // reliability level will be low, medium, high and will have to do with required car repairs
    QString reliabilityLevel;
};

#endif // CAR_H
