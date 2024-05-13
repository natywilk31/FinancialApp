/// This is the header class for the model of our app,
/// which will control all logic and hold the data.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef MODEL_H
#define MODEL_H

#include "Car.h"
#include "player.h"
#include "stock.h"
#include "house.h"
#include <QWidget>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model();
    int difficulty;
    QTimer *timer;

private:
    // Player object
    Player player;
    QList<Car> cars;
    QList<House> houses;
    QList<Stock> stocks;

    // for tracking time
    int day;
    void weekPassed();
    void monthPassed();
    void yearPassed();

    // check if all objectives are done
    void checkObjectives();

    // setup
    void sendInitialPricesToChart(QList<Stock> stocks);

    // decide if car breaks down, house needs repair
    void taxUser();
    void willCarBreakDown();
    void willHouseNeedRepair();

signals:

    // setup
    void drawAccounts(Player player);
    void cantAffordAsset(QString assetType);

    // setup
    void drawAssetsTab(QList<Car> cars, QList<House> houses);
    void setStockPrices(QList<Stock> stocks);
    void drawDate(int day);

    // get stock prices
    void sendStockPrice(QString);

    // things to redraw each turn
    void drawPlayersAssets(Car * car, House * house);
    void drawDebts(Player player);
    void sendPricesToCharts(QList<Stock>);
    void drawRate(float rate, float minimumPayment);
    void stockShareAmount(int, int);

    // signals for saying that a car / house was able to be afforded
    void carSuccessfullyBought();
    void houseSuccessfullyBought();

    // signals for reaching objectives
    void reached10k();
    void reached100k();
    void bought3Stocks();
    void daysDebtFree30();
    void reachedStocks10k();
    void repaidLoan();

    // for random event
    void carBrokeDown();

public slots:
    // tracking time
    void dayPassed();
    /**
     * @brief Function that emits all neccessary signal to the view to draw all aspects.
     *
     */
    void setFullUi();
    /**
     * @brief Set the difficulty of the model. Changes Player and stocks fields.
     *
     * @param difficulty Difficulty level
     */
    void setDifficulty(int difficulty);

    // For banking
    void transferMoney(double amount, QString sendingAccount, QString receivingAccount);
    /**
     * @brief sendLoanInfo Recieves the info to calculate the rate.
     * @param amount Amount of the loans.
     * @param lengthStr The length of the loan.
     */
    void sendLoanInfo(int amount, QString lengthStr);
    /**
     * @brief acceptLoanModel Recieves the info to accept the loan.
     * @param loanName Name of the loan.
     * @param rateStr Rate of the loan.
     * @param lengthStr The length of the loan.
     * @param amount Amount of the loan.
     */
    void acceptLoanModel(QString loanName, QString rateStr, QString lengthStr, float amount);
    /**
     * @brief payLoanModel Recieves the loan payment information and pays off the loan.
     * @param loanIndex Which loan is chosen.
     * @param amount The amount of money which is being paid.
     * @param account From which account is it being paid from.
     */
    void payLoanModel(int loanIndex, float amount, QString account);

    // buying and selling assets
    void stockBought(int stockIndex);
    void stockSold(int stockIndex);
    void carBought(int carIndex);
    void houseBought(int houseIndex);
};

#endif // MODEL_H
