/// This is the header file for a stock.
/// It has all the functionality for rising and dropping prices, time passing, and risk.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef STOCK_H
#define STOCK_H

#include <QRandomGenerator>
#include "qlist.h"
class Stock
{
public:
    //basic stock constructor
    Stock();
    //stock constructor that takes in a marketvalue and a risk value
    Stock(double marketValue, int risk);
    // method for once an ingame week passes, changes stock values
    void weekPassed() ;
    //getter methods for all stock variables
    int getPrice() const;
    int getRisk();
    QList<int> getMarketHistory() const;

private:
    //variable for the value of the stock
    int marketValue;
    //variable for the risk of the stock, 0 for low risk and 1 for high risk
    int risk;
    //setter for stock value
    void setMarketValue(double newMarketValue);
    //method to change the low risk stock value
    int changeLowRiskMarketValue();
    //method to change the high risk stock value
    int changeHighRiskMarketValue();
    //variable for the stock value history
    QList<int> marketValueHistory;

};

#endif // STOCK_H


