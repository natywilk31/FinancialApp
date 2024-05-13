/// This is the implementation file for a stock.
/// It has all the functionality for rising and dropping prices, time passing, and risk.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "stock.h"

Stock::Stock()
{
    marketValue = 0;
    risk = 0;
    marketValueHistory = QList<int>();
}
Stock::Stock(double marketValue, int risk)
{
    this->marketValue = marketValue;
    this->risk = risk;
    marketValueHistory = QList<int>();
}

int Stock::getPrice() const
{
    return this->marketValue;
}

int Stock::getRisk()
{
    return this->risk;
}

QList<int> Stock::getMarketHistory() const
{
    return this->marketValueHistory;
}

void Stock::weekPassed()
{
    if(this->risk == 0)
    {
        this->changeLowRiskMarketValue();
    }
    else
    {
        this->changeHighRiskMarketValue();
    }
}

void Stock::setMarketValue(double newMarketValue)
{
    this->marketValue = newMarketValue;
}

int Stock::changeHighRiskMarketValue()
{
    int stockChance = QRandomGenerator::global()->bounded(1,101);
    double stockChangeAmount = QRandomGenerator::global()->bounded(1,4);
    int lastPoint;

    //if the history is empty, the last point is the current point
    if(!(this->marketValueHistory.isEmpty()))
    {
        lastPoint = this->marketValueHistory.back();
    }
    else
    {
        lastPoint = this->marketValue;
    }

    if(this->getPrice() < 2)
    {
        this->setMarketValue(1);
    }

    //if there is positive historical data, stock has inclination to go up
    if(this->marketValue > lastPoint)
    {
        if(stockChance < 40)
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue * stockChangeAmount);
            return this->marketValue;
        }
        else if(stockChance > 40 && stockChance < 80)
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue / stockChangeAmount);
            return this->marketValue;
        }
        else if(stockChance > 80 && stockChance < 95)
        {
            this->marketValueHistory.append(this->marketValue);
            return this->marketValue * 1.5;

        }
        else
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue * 5);
            return this->marketValue;
        }
    }
    //otherwise the stock is more likely to go down
    else
    {
        if(stockChance < 40)
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue / (stockChangeAmount));
            return this->marketValue;
        }
        else if(stockChance > 40 && stockChance < 80)
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue * stockChangeAmount);
            return this->marketValue;
        }
        else if(stockChance > 80 && stockChance < 95)
        {
            this->marketValueHistory.append(this->marketValue);
            return this->marketValue / 2;
        }
        else
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue / 5);
            return this->marketValue;
        }
    }
}

int Stock::changeLowRiskMarketValue()
{
    int stockChance = QRandomGenerator::global()->bounded(1,101);
    int lastPoint;

    if(!(this->marketValueHistory.isEmpty()))
    {
        lastPoint = this->marketValueHistory.back();
    }
    else
    {
        lastPoint = this->marketValue;
    }

    if(this->getPrice() < 2)
    {
        this->setMarketValue(1);
    }

    //if there is positive historical data, stock has inclination to go up
    if(this->marketValue >= lastPoint)
    {
        if(stockChance < 75)
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue * 1.05);
            return this->marketValue;
        }
        else if(stockChance > 75 && stockChance < 85)
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue * 1.2);
            return this->marketValue;
        }
        else if(stockChance > 85 && stockChance < 95)
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue / 1.1);
            return this->marketValue;
        }

        else
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue * 1.8);
            return this->marketValue;
        }
    }
    //otherwise the stock is more likely to go down
    else
    {
        //chance to go down slightly
        if(stockChance < 60)
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue / 1.1);
            return this->marketValue;
        }
        //chance to go down
        else if(stockChance > 60 && stockChance < 75)
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue / 1.2);
            return this->marketValue;
        }
        //chance to go up slightly
        else if(stockChance > 75 && stockChance < 95)
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue * 1.2);
            return this->marketValue;
        }
        //chance to fall
        else
        {
            this->marketValueHistory.append(this->marketValue);
            this->setMarketValue(this->marketValue / 2);
            return this->marketValue;
        }
    }

}
