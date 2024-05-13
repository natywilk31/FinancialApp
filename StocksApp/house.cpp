/// This is the implementation file for a house.
/// It stores a price and a quality level.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "house.h"
#include <QRandomGenerator>


House::House()
{

}

House::House(double difficulty,int quality)
{
    // use difficulty to set price
    price = difficulty*100000;

    // figure out quality level based on the price
    if (quality == 0)
        reliabilityLevel = "low";
    else if (quality == 1)
        reliabilityLevel = "medium";
    else
        reliabilityLevel = "high";
}

void House::setPrice(int newPrice)
{
    price = newPrice;
}

int House::getPrice()
{
    return price;
}

void House::yearPassed(){
    int chanceOfDepreciation = QRandomGenerator::global()->bounded(100);

    if(price < 30000){
        // 50% chance house 10% appreciates
        // 25% chance of 10% depreciation
        if(chanceOfDepreciation < 50){
            price *= 1.10;
        }
        else if(chanceOfDepreciation < 75 && price < 5000){
            price = price - (price * .10);
        }
    }
    else if(price < 50000){
        // 55% chance house 12% appreciates
        // 20% chance of 9% depreciation
        if(chanceOfDepreciation < 55){
            price *= 1.12;
        }
        else if(chanceOfDepreciation < 75 && price < 8000){
            price = price - (price * .09);
        }
    }
    else if(price < 100000){
        // 58% chance house 12% appreciates
        // 15% chance of 8% depreciation
        if(chanceOfDepreciation < 58){
            price *= 1.12;
        }
        else if(chanceOfDepreciation < 76 && price < 25000){
            price = price - (price * .08);
        }
    }
    else{
        // 65% chance house 20% appreciates
        // 5% chance of 5% depreciation
        if(chanceOfDepreciation < 65){
            price *= 1.20;
        }
        else if(chanceOfDepreciation < 70 && price < 75000){
            price = price - (price * .05);
        }
    }
}
