/// This is the implementation file for a player.
/// It tracks their assets, stocks, savings, etc.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "player.h"
#include "qdebug.h"

Player::Player() {}

Player::Player(int difficulty)
{

    // different starting stats and salary based on difficulty
    switch(difficulty){
    case 1:
        savings = 10000;
        checking = 10000;
        weeklySalary = 200;
        break;
    case 2:
        savings = 500;
        checking = 500;
        weeklySalary = 200;
        break;
    case 3:
        savings = 0;
        checking = 0;
        weeklySalary = 100;
        break;
    }

    // set this variable so it can immediately be reliably accessed from other classes
    assetAmount = savings + checking;

    // hash map of cars and houses, user can have multiple of each
    cars = QHash<int, Car>();
    houses = QHash<int, House>();

    loans = QList<Loan>();

    // set up stocks
    stocks = QHash<int, std::vector<int>>();
    stocks.insert(0, std::vector<int>());
    stocks.insert(1, std::vector<int>());
    stocks.insert(2, std::vector<int>());
    stocks.insert(3, std::vector<int>());
    stocks.insert(4, std::vector<int>());
    stocks.insert(5, std::vector<int>());
}

void Player::weekPassed()
{
    // weekly salary goes into checking every 7 days
    if(debtAmount > 0){
        int payOffAmount = weeklySalary - debtAmount;
        checking = payOffAmount;
        debtAmount -= weeklySalary;
        if(debtAmount < 0){
            debtAmount = 0;
        }
    }
    else{
        checking += weeklySalary;
    }
    // savings accrues .25% interest each week
    savings *= 1.0025;
    // each week add up all assets so it can be accessed from other classes
    assetAmount = weeklySalary + savings + checking + totalAmountInStockHoldings +
        amountInCars + amountInHouses;
}

void Player::monthPassed()
{
    int index = 0;
    for(Loan &loan : loans){
        if (loan.isPaid())
        {
            loans.remove(index);
            loanCount--;
        }
        else
        {
            // Add interest to the current loan
            loan.addInterest();
        }
        index++;
    }
}

float Player::getSalary(){
    return weeklySalary * 52;
}

float Player::getSavings()
{
    return savings;
}

void Player::setSavings(float amount)
{
    savings = amount;
}

float Player::getChecking()
{
    return checking;
}

void Player::setChecking(float amount)
{
    checking = amount;
    if(checking < 0){
        setDebtAmount(checking * -1);
    }
}

float Player::getAssetAmount()
{
    return assetAmount;
}

void Player::setAssetAmount(float amount)
{
    assetAmount = amount;
}

float Player::getDebtAmount()
{
    return debtAmount;
}

void Player::setDebtAmount(float amount)
{
    debtAmount = amount;
}

Car Player::getCar(int index)
{
    return cars.value(index);
}

QHash<int, Car> &Player::getCars()
{
    return cars;
}

void Player::addCar(Car& newCar)
{
    cars.insert(carCount, newCar);
    carCount++;
}

House Player::getHouse(int index)
{
    return houses.value(index);
}

QHash<int, House> &Player::getHouses()
{
    return houses;
}

void Player::addHouse(House& newHouse)
{
    houses.insert(houseCount, newHouse);
    houseCount++;
}

Loan Player::getLoan(int index)
{
    return loans.value(index);
}

void Player::payLoan(int index,float amount,QString account)
{

    // figure out which account, if not enough, dont do it
    if (account=="Savings"){
        if(savings>amount){
            savings-=amount;
            savings+=loans[index].payLoan(amount);
        }
    }
    else{
        if(checking>amount){
            checking-=amount;
            checking+=loans[index].payLoan(amount);
        }
    }
    if (loans[index].isPaid()){
        loans.removeAt(index);
    }
}

QList<Loan> &Player::getLoans()
{
    return loans;
}

float Player::getLoansAmount()
{
    loanAmount = 0;
    for(Loan loan : loans){
        loanAmount += loan.getAmount();
    }
    return loanAmount;
}

void Player::addLoan(Loan& newLoan)
{
    loans.append(newLoan);
    loanAmount = newLoan.getAmount();
    loanCount++;
    setChecking(checking + newLoan.getAmount());
}

void Player::buyStock(int stockIndex, int price)
{
    std::vector<int> &stockShareVector = stocks[stockIndex];
    stockShareVector.push_back(price);
    checking -= price;
    amountInStock += price;
    totalAmountInStockHoldings += price;
}

void Player::sellStock(int stockIndex, int currentStockPrice)
{
    std::vector<int> &stockShareVector = stocks[stockIndex];
    int buyPrice = stockShareVector.back();
    checking += (buyPrice + (currentStockPrice - buyPrice));
    amountInStock -= buyPrice;
    totalAmountInStockHoldings -= (buyPrice + (currentStockPrice - buyPrice));
    stockShareVector.pop_back();
}

void Player::buyCar(Car newCar)
{
    cars.insert(carCount, newCar);
    carCount++;

    // do the operations of purchasing a car
    checking -= newCar.getPrice();
    amountInCars += newCar.getPrice();
    totalCarValue += newCar.getPrice();
}

void Player::sellCar(int carIndex)
{
    Car car = cars.value(carIndex);
    int carPrice = car.getPrice();
    amountInCars -= carPrice;
    checking += carPrice;

    cars.remove(carIndex);
    carCount--;
}

void Player::buyHouse(House newHouse)
{
    houses.insert(carCount, newHouse);
    houseCount++;

    // update assets and banking
    checking -= newHouse.getPrice();
    amountInHouses += newHouse.getPrice();
    totalHouseValue += newHouse.getPrice();
}

void Player::sellHouse(int houseIndex)
{
    House house = houses.value(houseIndex);
    int housePrice = house.getPrice();
    amountInHouses -= housePrice;
    checking += housePrice;

    // update assets and banking
    houses.remove(houseIndex);
    houseCount--;
}

bool Player::isShareAtIndex(int stockIndex)
{
    std::vector<int> stockShareVector = stocks[stockIndex];
    return stockShareVector.size() > 0;
}

int Player::sharesOfStockAtIndex(int stockIndex)
{
    std::vector<int> stockShareVector = stocks[stockIndex];
    return stockShareVector.size();
}

int Player::getMoneyInStocks()
{
    return amountInStock;
}

int Player::getMoneyInCars()
{
    return amountInCars;
}

int Player::getMoneyInHouses()
{
    return amountInHouses;
}

int Player::getTotalValueOfCars(){
    return totalCarValue;
}

void Player::totalValueOfCars(){
    totalCarValue = 0;
    for(Car car : cars){
        totalCarValue += car.getPrice();
    }
    assetAmount = savings + checking + totalAmountInStockHoldings +
                  totalCarValue + totalHouseValue;
}

int Player::getTotalValueOfHouses(){
    return totalHouseValue;
}

void Player::totalValueOfHouses(){
    totalHouseValue = 0;
    for(House house : houses){
        totalHouseValue += house.getPrice();
    }
    assetAmount = savings + checking + totalAmountInStockHoldings +
                  totalCarValue + totalHouseValue;
}

int Player::getTotalValueOfStock()
{
    return totalAmountInStockHoldings;
}

void Player::totalStockShareValue(QList<Stock> gameStocks)
{
    totalAmountInStockHoldings = 0;
    for(int i = 0; i < gameStocks.size(); i++)
    {
        if(sharesOfStockAtIndex(i) > 0)
        {
            const std::vector<int> &stockShareVector = stocks[i];
            for(auto stockPrice : stockShareVector)
            {
                totalAmountInStockHoldings += (stockPrice + (gameStocks[i].getPrice() - stockPrice));
            }
        }
    }
    assetAmount = savings + checking + totalAmountInStockHoldings +
                  totalCarValue + totalHouseValue;
}
