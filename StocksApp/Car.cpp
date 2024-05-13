/// This is the implementation class of our car.
/// It calculates the price based on difficulty, and then it stores the price and reliability.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "Car.h"
#include <QRandomGenerator>


Car::Car()
{

}

Car::Car(double difficulty, int carQuality, QString name) : name(name)
{
    // we use difficulty to determine the price of a car
    price = 1000*difficulty;

    // set reliability level, which is based on price
    if (carQuality == 0)
        reliabilityLevel = "low";
    else if (carQuality == 1)
        reliabilityLevel = "medium";
    else
        reliabilityLevel = "high";
}

void Car::monthPassed(){
    int chanceOfDepreciation = QRandomGenerator::global()->bounded(100);

    if(price < 300){
        // 15% chance car depreciates
        if(chanceOfDepreciation < 15 && price > 50){
            // car depreciates by 15%
            price = price - (price * .15);
        }
    }
    else if(price < 500){
        // 8% chance car depreciates
        if(chanceOfDepreciation < 8 && price > 100){
            // car depreciates by 15%
            price = price - (price * .15);
        }
    }
    else if(price < 1000){
        // 5% chance car depreciates
        if(chanceOfDepreciation == 0 && price > 200){
            // car depreciates by 15%
            price = price - (price * .15);
        }
    }
    else{
        // 15% chance car appreciates
        // 1% chance of depreciation
        if(chanceOfDepreciation < 15){
            price *= 1.15;
        }
        else if(chanceOfDepreciation < 16 && price < 300){
            price = price - (price * .15);
        }
    }
}

void Car::setPrice(int newPrice)
{
    price = newPrice;
}

int Car::getPrice()
{
    return price;
}

QString Car::getReliabilityLevel(){
    return reliabilityLevel;
}
