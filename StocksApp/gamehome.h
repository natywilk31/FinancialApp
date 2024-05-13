/// This is the header file for our home screen,
/// which shows the user's data and actions they can take.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef GAMEHOME_H
#define GAMEHOME_H

#include "QtCharts/qchartview.h"
#include "QtCharts/qlineseries.h"
#include "celebrationscreen.h"
#include "utilitydialog.h"
#include "model.h"
#include <QDialog>
#include <QLabel>
#include <QChart>
#include <QValueAxis>
#include "QStringListModel"

namespace Ui
{
class GameHome;
}

class GameHome : public QDialog
{
    Q_OBJECT

public:
    explicit GameHome(QWidget *parent = nullptr);
    ~GameHome();

    // The model that  will contain everything about that instance of the game.
    Model* m;

private:
    Ui::GameHome *ui;
    QMap<int, QLabel> labelMap;

    // utility dialog to pop up when player tries to buy something they cant afford
    utilityDialog cantAfford;
    // a dialog that will pop up when user has completed all objectives
    celebrationScreen celebration;
    // tipsScreen tips;

    QChart * assetChart;
    QLineSeries * pointSeriesAssets;
    QChartView * assetView;
    QValueAxis * assetAxisY;

    QChart * debtChart;
    QLineSeries * pointSeriesDebts;
    QChartView * debtView;
    QValueAxis * debtAxisY;

    QChart * aaplChart;
    QLineSeries * aaplPointSeries;
    QChartView * aaplView;
    QValueAxis * aaplAxisY;

    QChart * googChart;
    QLineSeries * googPointSeries;
    QChartView * googView;
    QValueAxis * googAxisY;

    QChart * msftChart;
    QLineSeries * msftPointSeries;
    QChartView * msftView;
    QValueAxis * msftAxisY;

    QChart * koChart;
    QLineSeries * koPointSeries;
    QChartView * koView;
    QValueAxis * koAxisY;

    QChart * metaChart;
    QLineSeries * metaPointSeries;
    QChartView * metaView;
    QValueAxis * metaAxisY;

    QChart * xomChart;
    QLineSeries * xomPointSeries;
    QChartView * xomView;
    QValueAxis * xomAxisY;


    QStringListModel * loanModelBox;
    QStringList loanItemList;

    int dayNum = 0;

    // track how many objectives we've done so we can figure out when all are done
    int objectivesCompleted;

    // bools to track whether each objective has been completed
    bool objective1Done;
    bool objective2Done;
    bool objective3Done;
    bool objective4Done;
    bool objective5Done;
    bool objective6Done;


signals:
    /**
     * @brief Sends a signal to the model that it wants to recieve and redraw the entire ui.
     */
    void getFullUi();
    /**
     * @brief Sends a signal to set the difficulty of the model.
     *
     * @param difficulty Level of difficulty to set the model to.
     */
    void setDifficulty(int difficulty);

    /**
     * @brief sendCarPrice a signal to convey the price of the car bought
     * @param carIndex the index of the car in the list, which will also be passed back and forth
     */
    void sendCarPrice(int carIndex);

    /**
     * @brief sendHousePrice a signal to convey the price of the house bought
     * @param houseIndex the index of the house in the list, which will also be passed back and forth
     */
    void sendHousePrice(int houseIndex);

    void sendStockPrice(int stockIndex);
    // For banking
    void computeMoneyTransfer(double amount, QString sendingAccount, QString receivingAccount);
    void sendLoanInfo(int amount, QString length);
    void acceptLoanModel(QString loanName, QString rateStr, QString lengthStr, float amount);
    void payLoanModel(int loanIndex,float amount,QString account);
    // signals for objectives
    void reachedCarObjective();
    void reachedHouseObjective();
    void objectivesFinished();

    void sellStockPrice(int);

    // signal to tell the celebration screen to start drawing itself
    void updateCelebrateDrawing();


public slots:
    /**
     * @brief Sets the view and model for the new instance of the game by setting the difficulty of the model and drawing the entire ui.
     *
     * @param difficulty The level of difficulty sent from the select difficulty screen.
     */
    void setUpGame(int difficulty);
    /**
     * @brief Sets the text of all of the accounts.
     *
     * @param player Is passed the player class to retrieve the information from.
     */
    void drawAccounts(Player player);

    /**
     * @brief drawAssetsTab draws all of the needed information in the assets tab.
     * @param cars List of cars for the assets tab to draw.
     */
    void drawAssetsTab(QList<Car> cars, QList<House> houses);

    // void drawPlayersAssets(Car *car, House *house); // will also need to include array of stocks

    /**
     * @brief drawDate Draws the date onto the ui
     * @param day The day number
     */
    void drawDate(int day);

    /**
     * @brief readyForCelebrate catch the signal telling us to show the celebration screen
     */
    void readyForCelebrate();

    void setStockPrices(QList<Stock> stocks);

    // slots for passing car prices back and forth
    void sendLeftCarPrice();
    void sendMiddleCarPrice();
    void sendRightCarPrice();

    // slots for passing house prices back and forth
    void sendLeftHousePrice();
    void sendMiddleHousePrice();
    void sendRightHousePrice();

    void sellStock1Price();
    void sellStock2Price();
    void sellStock3Price();
    void sellStock4Price();
    void sellStock5Price();
    void sellStock6Price();


    void sendStock1Price();
    void sendStock2Price();
    void sendStock3Price();
    void sendStock4Price();
    void sendStock5Price();
    void sendStock6Price();


    void setCharts(QList<Stock> stocks);

    void setStockShareAmount(int, int);

    // takes a string of what can't be afforded and displays that in a dialog
    void cantAffordAsset(QString assetType);

    // catch signals telling us that we've reached each objectives, change it to green on view
    void changeCarObjectiveToGreen();
    void changeHouseObjectiveToGreen();
    void changeSavingsObjectiveToGreen();
    void changeStocksObjectiveToGreen();
    void changeNetWorthObjectiveToGreen();
    void changeDebtFreeObjectiveToGreen();

    // For banking
    void transferMoney();
    void drawDebts(Player player);
    void drawRate(float rate, float minimumPayment);
    void calculateRate();
    void acceptLoan();
    void payLoan();
    // Popups
    void displayTips();
    void displayLoanHelp();
};

#endif // GAMEHOME_H
