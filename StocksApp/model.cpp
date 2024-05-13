/// This is the implementation file for the model of our app,
/// which will control all logic and hold the data.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "model.h"
#include "qtimer.h"
#include "qdebug.h"
Model::Model()
{
    // set up stocks and player, time
    player = Player();
    day = 0;
    stocks = QList<Stock>();
    stocks.append(Stock(50,0));
    stocks.append(Stock(100,0));
    stocks.append(Stock(30,0));
    stocks.append(Stock(50,1));
    stocks.append(Stock(100,1));
    stocks.append(Stock(60,1));

    timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &Model::dayPassed);
}

void Model::dayPassed()
{
    checkObjectives();
    willCarBreakDown();
    willHouseNeedRepair();


    day += 1;

    if (day % 7 == 0)
    {
        weekPassed();
    }
    if (day % 30 == 0)
    {
        monthPassed();
    }
    if( day % 365 == 0){
        yearPassed();
    }

    emit drawAccounts(player);
    emit drawDate(day);
    if(day == 1){
        emit sendPricesToCharts(stocks);
    }

}

void Model::weekPassed()
{
    player.weekPassed();

    for(int i = 0; i < stocks.size(); i++)
    {
        stocks[i].weekPassed();
        player.totalStockShareValue(stocks);
    }

    emit setStockPrices(stocks);
}

void Model::monthPassed()
{
    player.monthPassed();

    QHash<int, Car> &cars = player.getCars();
    for(Car &car : cars){
        car.monthPassed();
    }

    player.totalValueOfCars();
     emit drawDebts(player);
}

void Model::yearPassed(){
    QHash<int, House> &houses = player.getHouses();
    for(House &house : houses){
        house.yearPassed();
    }

    taxUser();
    player.totalValueOfHouses();
}

void Model::checkObjectives()
{
    // checks for objectives
    if (player.getSavings() >= 10000)
    {
        emit reached10k();
    }

    if (player.getAssetAmount() >= 100000)
    {
        emit reached100k();
    }

    if (player.getTotalValueOfStock() >= 10000)
    {
        emit reachedStocks10k();
    }
}

void Model::taxUser(){
    // tax the user once per year
    float salary = player.getSalary();
    float incomeTax = (salary * .05) + (player.getChecking() * .05);

    float propertyValue = player.getTotalValueOfHouses();
    float propertyTax = propertyValue * .0055;

    player.setChecking(player.getChecking() - (incomeTax + propertyTax));
    emit cantAffordAsset("Tax Season is Upon Us! "
                         "\n Given your income, you have been taxed $"
                         + QString::number(incomeTax) + ". \n You have also been taxed $" + QString::number(propertyTax) + " on your houses");
}

void Model::willCarBreakDown(){
    // use random to see if the car will break down
    bool hasCar = player.getCars().count() > 0;

    if(hasCar){
        int chanceOfBreakDown = QRandomGenerator::global()->bounded(200);
        if(chanceOfBreakDown < 1){
            player.setChecking(player.getChecking() - 250);
            emit cantAffordAsset("Uh Oh! "
                                 "\n Your car broke down, you will lose $"
                                 + QString::number(250) + ". \n in order to fix it.");
        }
    }
}

void Model::willHouseNeedRepair(){
    bool hasHouse = player.getHouses().count() > 0;

    if(hasHouse){
        int chanceOfNeededRepair = QRandomGenerator::global()->bounded(200);
        if(chanceOfNeededRepair < 0){
            player.setChecking(player.getChecking() - 500);
            emit cantAffordAsset("Uh Oh! "
                                 "\n Your house needs a repair, you will lose $"
                                 + QString::number(500) + ". \n in order to fix it.");
        }
    }
}

void Model::setDifficulty(int difficultyLevel)
{
    // depending on difficulty, we will have different prices for cars, houses, etc
    difficulty = difficultyLevel;
    player = Player(difficultyLevel);
    cars.append(Car((double)difficulty / 4, 0, "Toyota"));
    cars.append(Car((double)difficulty / 2, 1, "Kia"));
    cars.append(Car(difficulty, 2, "BMW"));
    houses.append(House((double)difficulty / 4, 0));
    houses.append(House((double)difficulty / 2, 1));
    houses.append(House(difficulty, 0));
    timer->start();
}

void Model::sendLoanInfo(int amount, QString lengthStr) {
    if(amount>0){

        float rate = (amount / player.getAssetAmount()-player.getDebtAmount())/8;
        if(rate<0 || rate>20){
            rate=20;
        }
        float loanLength = std::stof(lengthStr.toStdString());
        float minimumPayment= amount/(loanLength*12);

        emit drawRate(rate, minimumPayment);
    }
}

void Model::acceptLoanModel(QString loanName,QString rateStr,QString lengthStr, float amount) {
    float rate = std::stof(rateStr.mid(1).toStdString());
    float loanLength = std::stof(lengthStr.toStdString());
    Loan loan=Loan(loanName,amount,day,(loanLength*12),rate);
    player.addLoan(loan);

    emit drawDebts(player);
}

void  Model::payLoanModel(int loanIndex,float amount, QString account){
    player.payLoan(loanIndex, amount, account);
    emit drawDebts(player);
    emit repaidLoan();
}

void Model::setFullUi()
{
    emit drawAccounts(player);
    emit drawAssetsTab(cars, houses);
    emit drawDebts(player);
    emit stockShareAmount(0, 0);
}

void Model::carBought(int carIndex)
{
    Car car = cars[carIndex];
    // see if we can afford it
    if (car.getPrice() > player.getChecking())
    {
        emit cantAffordAsset("Sorry, you can't afford this car.");
    }
    // if we pass the check, we add it to the players car list, update accounts, let gamehome know we bought it successfully
    else
    {
        player.buyCar(car);
        emit drawAccounts(player);
        emit carSuccessfullyBought();
    }
}

void Model::houseBought(int houseIndex)
{
    House house = houses[houseIndex];
    // check if we can afford the house
    if (house.getPrice() > player.getChecking())
    {
        emit cantAffordAsset("Sorry, you can't afford this house.");
    }
    // if we pass the check, we add it to the players houses list, and redraw accounts and let gamehome know we could afford the house
    else{
        player.buyHouse(house);
        emit drawAccounts(player);
        emit houseSuccessfullyBought();
    }
}

void Model::stockSold(int stockIndex)
{
    Stock stock = stocks[stockIndex];
    if(player.isShareAtIndex(stockIndex))
    {
        player.sellStock(stockIndex, stock.getPrice());
        emit drawAccounts(player);
        emit stockShareAmount(stockIndex, player.sharesOfStockAtIndex(stockIndex));
    }
}

void Model::stockBought(int stockIndex)
{
    Stock stock = stocks[stockIndex];
    if(!(player.getChecking() < stock.getPrice()))
    {
        player.buyStock(stockIndex, stock.getPrice());
        emit drawAccounts(player);
        emit stockShareAmount(stockIndex, player.sharesOfStockAtIndex(stockIndex));
    }
    else
    {
        emit cantAffordAsset("Sorry, you can't afford this stock");
    }
}

void Model::transferMoney(double amount, QString sendingAccount, QString receivingAccount)
{
    // we will check what account is sending and if they have enough money in that account to send

    if (sendingAccount == QString("Savings")  && amount > player.getSavings())
    {
        emit cantAffordAsset("Sorry, you don't have enough in savings \n to make this transfer.");
        return;
    }

    if (sendingAccount == QString("Checkings")  && amount > player.getChecking())
    {
        emit cantAffordAsset("Sorry, you don't have enough in checking \n to make this transfer.");
        return;
    }

    // we can afford to do the transfer, we subtract from sending and add to receiving
    if(sendingAccount == QString("Savings") && receivingAccount == QString("Checkings"))
    {
        player.setSavings(player.getSavings() - amount);
        player.setChecking(player.getChecking() + amount);
    }
    else if(sendingAccount == QString("Checkings") && receivingAccount == QString("Savings"))
    {
        player.setSavings(player.getSavings() + amount);
        player.setChecking(player.getChecking() - amount);
    }
    // update accounts and draw
    emit drawAccounts(player);
}
