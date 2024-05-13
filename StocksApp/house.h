/// This is the header file for a house.
/// It has a price as well as a quality level.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef HOUSE_H
#define HOUSE_H

#include <QString>

class House
{
public:
    // default constructor as well as constructor to input difficulty and quality
    House();
    House(double difficulty, int quality);

    // getter setter for price
    void setPrice(int newPrice);
    int getPrice();

    void yearPassed();

private:
    int price;
    // low medium high, will correlate with the chances of a house repair being needed
    QString reliabilityLevel;

};

#endif // HOUSE_H
