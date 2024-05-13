/// This is the header file for the player in our game.
/// It will store their assets, debts, money, etc.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef PLAYER_H
#define PLAYER_H

#include <QHash>
#include "Car.h"
#include "loan.h"
#include "house.h"
#include "stock.h"

class Player
{
public:
    Player();
    Player(int difficulty);

    // certain things happen each week / month, these encapsulate those events
    void weekPassed();
    void monthPassed();

    float getSalary();

    // getter setter for savings
    float getSavings();
    void setSavings(float);

    // getter setter for checking
    float getChecking();
    void setChecking(float);

    // getter setter for amount in assets
    float getAssetAmount();
    void setAssetAmount(float amount);

    // getter setter for debt
    float getDebtAmount();
    void setDebtAmount(float amount);

    // getter adder for car
    Car getCar(int index);
    QHash<int, Car> &getCars();
    void addCar(Car& newCar);

    // getter adder for house
    House getHouse(int index);
    QHash<int, House> &getHouses();
    void addHouse(House& newHouse);

    // methods to pay, add, view a loan
    Loan getLoan(int index);
    void payLoan(int index, float amount, QString account);
    QList<Loan> &getLoans();
    void addLoan(Loan& newLoan);
    float getLoansAmount();

    // buy and sell stock
    void buyStock(int stockIndex, int price);
    void sellStock(int stockIndex, int currentStockPrice);

    // buy and sell car
    void buyCar(Car newCar);
    void sellCar(int carIndex);

    // buy and sell house
    void buyHouse(House newHouse);
    void sellHouse(int houseIndex);

    // methods to get info on stocks
    bool isShareAtIndex(int stockIndex);
    int sharesOfStockAtIndex(int stockIndex);

    // getters for total money in stocks, cars, houses
    int getMoneyInStocks();
    int getMoneyInCars();
    int getMoneyInHouses();

    // getters for cars, stocks, house values
    int getTotalValueOfCars();
    void totalValueOfCars();
    int getTotalValueOfHouses();
    void totalValueOfHouses();
    int getTotalValueOfStock();
    void totalStockShareValue(QList<Stock> stocks);

private:
    //Weekly Salary
    float weeklySalary;
    //Amount in savings
    float savings;
    //Amount in checkings
    float checking;

    // asset and debt totals
    float assetAmount;
    float debtAmount = 0;
    float loanAmount = 0;

    int carCount = 0;
    int houseCount = 0;
    int loanCount = 0;

    // totals in stocks, cars, houses
    int amountInStock = 0;
    int amountInCars = 0;
    int amountInHouses = 0;
    int totalAmountInStockHoldings = 0;
    int totalCarValue = 0;
    int totalHouseValue = 0;

    // List of stocks the player has
    QHash<int, std::vector<int>> stocks;
    // Cars the player has
    QHash<int, Car> cars;
    // list of houses the player has
    QHash<int, House> houses;
    QList<Loan> loans;

};

#endif // PLAYER_H
