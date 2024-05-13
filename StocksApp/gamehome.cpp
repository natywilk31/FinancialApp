/// This is the implementation file for the home screen of our game.
/// It will show the user's data and actions they can take.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "gamehome.h"
#include "ui_gamehome.h"

GameHome::GameHome(QWidget *parent)
    : QDialog(parent), ui(new Ui::GameHome)
{
    // gamehome is where we do everything from, so it will own the model
    m = new Model();
    ui->setupUi(this);

    // initialize objective tracking stuff
    objectivesCompleted = 0;
    objective1Done = false;
    objective2Done = false;
    objective3Done = false;
    objective4Done = false;
    objective5Done = false;
    objective6Done = false;

    QFont font("System");
    QBrush back(QColor("#555555"));

    // set up stock charts
    assetChart = new QChart();
    assetChart->setTitleFont(font);
    assetChart->setBackgroundBrush(back);
    assetChart->setTitleBrush(Qt::white);
    assetChart->setTitle("Total Net Worth");
    assetChart->legend()->hide();
    assetChart->createDefaultAxes();
    pointSeriesAssets = new QLineSeries();
    pointSeriesAssets->append(QPoint(-1, 0));
    assetChart->addSeries(pointSeriesAssets);
    assetAxisY = new QValueAxis();
    assetChart->addAxis(assetAxisY, Qt::AlignLeft);
    pointSeriesAssets->attachAxis(assetAxisY);
    assetAxisY->setRange(0, 1);
    assetView = new QChartView(assetChart);
    assetView->setRenderHint(QPainter::Antialiasing);
    ui->assetChartLayout->addWidget(assetView);

    // set up debt chart
    debtChart = new QChart();
    debtChart->setTitleFont(font);
    debtChart->setTitleBrush(Qt::white);
    debtChart->setBackgroundBrush(back);
    debtChart->setTitle("Total Debt Value");
    debtChart->legend()->hide();
    debtChart->createDefaultAxes();
    pointSeriesDebts = new QLineSeries();
    pointSeriesDebts->append(QPoint(-1, 0));
    debtChart->addSeries(pointSeriesDebts);
    pointSeriesDebts->setColor(Qt::red);
    debtAxisY = new QValueAxis();
    debtChart->addAxis(debtAxisY, Qt::AlignLeft);
    pointSeriesDebts->attachAxis(debtAxisY);
    debtAxisY->setRange(0, 100);
    debtView = new QChartView(debtChart);
    debtView->setRenderHint(QPainter::Antialiasing);
    ui->debtChartLayout->addWidget(debtView);

    // apple chart
    aaplChart = new QChart();
    aaplChart->setTitleFont(font);
    aaplChart->setTitleBrush(Qt::white);
    aaplChart->setBackgroundBrush(back);
    aaplChart->setTitle("AAPL");
    aaplChart->legend()->hide();
    aaplChart->createDefaultAxes();
    aaplPointSeries = new QLineSeries();
    aaplPointSeries->append(QPoint(-1, 0));
    aaplPointSeries->append(QPoint(0, 49));
    aaplChart->addSeries(aaplPointSeries);
    aaplAxisY = new QValueAxis();
    aaplChart->addAxis(aaplAxisY, Qt::AlignLeft);
    aaplPointSeries->attachAxis(aaplAxisY);
    aaplAxisY->setRange(0, 50);
    aaplView = new QChartView(aaplChart);
    aaplView->setRenderHint(QPainter::Antialiasing);
    ui->aaplChartLayout->addWidget(aaplView);

    // google chart
    googChart = new QChart();
    googChart->setTitleFont(font);
    googChart->setTitleBrush(Qt::white);
    googChart->setBackgroundBrush(back);
    googChart->setTitle("GOOG");
    googChart->legend()->hide();
    googChart->createDefaultAxes();
    googPointSeries = new QLineSeries();
    googPointSeries->append(QPoint(-1, 0));
    googPointSeries->append(QPoint(0, 29));
    googChart->addSeries(googPointSeries);
    googAxisY = new QValueAxis();
    googChart->addAxis(googAxisY, Qt::AlignLeft);
    googPointSeries->attachAxis(googAxisY);
    googAxisY->setRange(0, 30);
    googView = new QChartView(googChart);
    googView->setRenderHint(QPainter::Antialiasing);
    ui->googChartLayout->addWidget(googView);

    // microsoft chart
    msftChart = new QChart();
    msftChart->setTitleFont(font);
    msftChart->setTitleBrush(Qt::white);
    msftChart->setBackgroundBrush(back);
    msftChart->setTitle("MSFT");
    msftChart->legend()->hide();
    msftChart->createDefaultAxes();
    msftPointSeries = new QLineSeries();
    msftPointSeries->append(QPoint(-1, 0));
    msftPointSeries->append(QPoint(0, 99));
    msftChart->addSeries(msftPointSeries);
    msftAxisY = new QValueAxis();
    msftChart->addAxis(msftAxisY, Qt::AlignLeft);
    msftPointSeries->attachAxis(msftAxisY);
    msftAxisY->setRange(0, 30);
    msftView = new QChartView(msftChart);
    msftView->setRenderHint(QPainter::Antialiasing);
    ui->msftChartLayout->addWidget(msftView);

    // ko chart
    koChart = new QChart();
    koChart->setTitleFont(font);
    koChart->setTitleBrush(Qt::white);
    koChart->setBackgroundBrush(back);
    koChart->setTitle("KO");
    koChart->legend()->hide();
    koChart->createDefaultAxes();
    koPointSeries = new QLineSeries();
    koPointSeries->append(QPoint(-1, 0));
    koPointSeries->append(QPoint(0, 49));
    koChart->addSeries(koPointSeries);
    koAxisY = new QValueAxis();
    koChart->addAxis(koAxisY, Qt::AlignLeft);
    koPointSeries->attachAxis(koAxisY);
    koAxisY->setRange(0, 30);
    koView = new QChartView(koChart);
    koView->setRenderHint(QPainter::Antialiasing);
    ui->koChartLayout->addWidget(koView);

    // meta charts
    metaChart = new QChart();
    metaChart->setTitleFont(font);
    metaChart->setTitleBrush(Qt::white);
    metaChart->setBackgroundBrush(back);
    metaChart->setTitle("META");
    metaChart->legend()->hide();
    metaChart->createDefaultAxes();
    metaPointSeries = new QLineSeries();
    metaPointSeries->append(QPoint(-1, 0));
    metaPointSeries->append(QPoint(0, 99));
    metaChart->addSeries(metaPointSeries);
    metaAxisY = new QValueAxis();
    metaChart->addAxis(metaAxisY, Qt::AlignLeft);
    metaPointSeries->attachAxis(metaAxisY);
    metaAxisY->setRange(0, 30);
    metaView = new QChartView(metaChart);
    metaView->setRenderHint(QPainter::Antialiasing);
    ui->metaChartLayout->addWidget(metaView);

    // xom charts
    xomChart = new QChart();
    xomChart->setTitleFont(font);
    xomChart->setTitleBrush(Qt::white);
    xomChart->setBackgroundBrush(back);
    xomChart->setTitle("XOM");
    xomChart->legend()->hide();
    xomChart->createDefaultAxes();
    xomPointSeries = new QLineSeries();
    xomPointSeries->append(QPoint(-1, 0));
    xomPointSeries->append(QPoint(0, 59));
    xomChart->addSeries(xomPointSeries);
    xomAxisY = new QValueAxis();
    xomChart->addAxis(xomAxisY, Qt::AlignLeft);
    xomPointSeries->attachAxis(xomAxisY);
    xomAxisY->setRange(0, 30);
    xomView = new QChartView(xomChart);
    xomView->setRenderHint(QPainter::Antialiasing);
    ui->xomChartLayout->addWidget(xomView);

    // set up loan box
    loanModelBox = new QStringListModel(this);

    //Create connections for drawing date, accounts, assets
    connect(m, &Model::drawAccounts, this, &GameHome::drawAccounts);
    connect(m, &Model::drawAssetsTab, this, &GameHome::drawAssetsTab);
    connect(m, &Model::drawDate, this, &GameHome::drawDate);
    connect(m, &Model::drawDebts, this, &GameHome::drawDebts);
    connect(m, &Model::drawRate, this, &GameHome::drawRate);

    // set up connections
    connect(m, &Model::setStockPrices, this, &GameHome::setStockPrices);
    connect(this, &GameHome::setDifficulty, m, &Model::setDifficulty);
    connect(this, &GameHome::getFullUi, m, &Model::setFullUi);
    // connect(this, &GameHome::getFullUi, this, &GameHome::displayTips);

    // connections for buying a car and sending the price
    connect(ui->buyCheapCar, &QPushButton::clicked, this, &GameHome::sendLeftCarPrice);
    connect(ui->buyMediumCar, &QPushButton::clicked, this, &GameHome::sendMiddleCarPrice);
    connect(ui->buyHighCar, &QPushButton::clicked, this, &GameHome::sendRightCarPrice);
    connect(this, &GameHome::sendCarPrice, m, &Model::carBought);

    // connections for buying a house and sending the price
    connect(ui->buyLeftHouse, &QPushButton::clicked, this, &GameHome::sendLeftHousePrice);
    connect(ui->buyMiddleHouse, &QPushButton::clicked, this, &GameHome::sendMiddleHousePrice);
    connect(ui->buyRightHouse, &QPushButton::clicked, this, &GameHome::sendRightHousePrice);
    connect(this, &GameHome::sendHousePrice, m, &Model::houseBought);

    // connections for buying and selling stocks
    connect(ui->stock1BuyButton, &QPushButton::clicked, this, &GameHome::sendStock1Price);
    connect(ui->stock2BuyButton, &QPushButton::clicked, this, &GameHome::sendStock2Price);
    connect(ui->stock3BuyButton, &QPushButton::clicked, this, &GameHome::sendStock3Price);
    connect(ui->stock4BuyButton, &QPushButton::clicked, this, &GameHome::sendStock4Price);
    connect(ui->stock5BuyButton, &QPushButton::clicked, this, &GameHome::sendStock5Price);
    connect(ui->stock6BuyButton, &QPushButton::clicked, this, &GameHome::sendStock6Price);
    connect(ui->stock1SellButton, &QPushButton::clicked, this, &GameHome::sellStock1Price);
    connect(ui->stock2SellButton, &QPushButton::clicked, this, &GameHome::sellStock2Price);
    connect(ui->stock3SellButton, &QPushButton::clicked, this, &GameHome::sellStock3Price);
    connect(ui->stock4SellButton, &QPushButton::clicked, this, &GameHome::sellStock4Price);
    connect(ui->stock5SellButton, &QPushButton::clicked, this, &GameHome::sellStock5Price);
    connect(ui->stock6SellButton, &QPushButton::clicked, this, &GameHome::sellStock6Price);
    connect(this, &GameHome::sellStockPrice, m, &Model::stockSold);
    connect(this, &GameHome::sendStockPrice, m, &Model::stockBought);
    connect(m, &Model::stockShareAmount, this, &GameHome::setStockShareAmount);
    connect(m, &Model::sendPricesToCharts, this, &GameHome::setCharts);
    connect(m, &Model::setStockPrices, this, &GameHome::setCharts);

    // connections to track when objectives are completed
    connect(this, &GameHome::reachedCarObjective, this, &GameHome::changeCarObjectiveToGreen);
    connect(this, &GameHome::reachedHouseObjective, this, &GameHome::changeHouseObjectiveToGreen);
    connect(m, &Model::carSuccessfullyBought, this, &GameHome::changeCarObjectiveToGreen);
    connect(m, &Model::reached10k, this, &GameHome::changeSavingsObjectiveToGreen);
    connect(m, &Model::reached100k, this, &GameHome::changeNetWorthObjectiveToGreen);
    connect(m, &Model::houseSuccessfullyBought, this, &GameHome::changeHouseObjectiveToGreen);
    connect(m, &Model::reachedStocks10k, this, &GameHome::changeStocksObjectiveToGreen);
    connect(m, &Model::repaidLoan, this, &GameHome::changeDebtFreeObjectiveToGreen);

    // connections to find when all objectives are finished, show celebration
    connect(this, &GameHome::objectivesFinished, this, &GameHome::readyForCelebrate);
    connect(ui->helpButton, &QPushButton::clicked, this, &GameHome::displayTips);

    // connection to detect when we can't afford an asset, according to the model. pop up our dialog
    connect(m, &Model::cantAffordAsset, this, &GameHome::cantAffordAsset);

    // connection for banking
    connect(this, &GameHome::computeMoneyTransfer, m, &Model::transferMoney);

    // transfer money between accounts
    connect(ui->transferButton, &QPushButton::clicked, this, &GameHome::transferMoney);
    // connection for loans
    connect(ui->calculateRateBox, &QPushButton::clicked, this, &GameHome::calculateRate);
    connect(ui->helpLoanButton, &QPushButton::clicked, this, &GameHome::displayLoanHelp);
    connect(this, &GameHome::sendLoanInfo, m, &Model::sendLoanInfo);
    connect(ui->loanButton, &QPushButton::clicked, this, &GameHome::acceptLoan);
    connect(this, &GameHome::acceptLoanModel, m, &Model::acceptLoanModel);
    connect(ui->payLoanButton, &QPushButton::clicked, this, &GameHome::payLoan);
    connect(this, &GameHome::payLoanModel, m, &Model::payLoanModel);


}

GameHome::~GameHome()
{
    delete ui;
}

void GameHome::drawAccounts(Player player)
{
    // Sets the text of accounts
    ui->savingsLabel->setText("Savings: $" + QString::number(player.getSavings(), 'f', 2));
    ui->checkingsLabel->setText("Checkings: $" + QString::number(player.getChecking(), 'f', 2));
    ui->moneyInCarPurchasesLabel->setText("Purchased Cars Total: $" + QString::number(player.getMoneyInCars(), 'f', 2));
    ui->totalCarValueLayout->setText("Total Car Value: $" + QString::number(player.getTotalValueOfCars(), 'f', 2));
    ui->moneyInHousePurchasesLabel->setText("Purchased Houses Total: $" + QString::number(player.getMoneyInHouses(), 'f', 2));
    ui->totalHouseValueLayout->setText("Total House Value: $" + QString::number(player.getTotalValueOfHouses(), 'f', 2));
    ui->moneyInStocksLabel->setText("Purchased Stock Total: $" + QString::number(player.getMoneyInStocks(), 'f', 2));
    ui->totalStockValueLabel->setText("Total Stock Value: $" + QString::number(player.getTotalValueOfStock(), 'f', 2));
    ui->totalAssetLabel->setText("Total Asset Value: $" + QString::number(player.getAssetAmount(), 'f', 2));

    ui->loanAmountLabel_2->setText("Total Loan Amount: $" + QString::number(player.getLoansAmount(), 'f', 2));
    ui->debtAmountLabel->setText("Total Debt Amount: $" + QString::number(player.getDebtAmount(), 'f', 2));
    ui->loanDebtAmountLabel->setText("Debt + Loan Amount: $" + QString::number((player.getDebtAmount() + player.getLoansAmount()), 'f', 2));

    pointSeriesAssets->append(dayNum, player.getAssetAmount());
    assetChart->removeSeries(pointSeriesAssets);
    assetChart->addSeries(pointSeriesAssets);
    if(player.getAssetAmount() > assetAxisY->max()){
        assetAxisY->setRange(0, player.getAssetAmount());
    }

    pointSeriesDebts->append(dayNum, (player.getDebtAmount() + player.getLoansAmount()));
    debtChart->removeSeries(pointSeriesDebts);
    debtChart->addSeries(pointSeriesDebts);
    if(player.getDebtAmount() > assetAxisY->max()){
        assetAxisY->setRange(0, (player.getDebtAmount() + player.getLoansAmount()));
    }
}

void GameHome::drawDebts(Player player)
{
    loanItemList.clear();
    ui->loanAccountBox->clear();
    loanItemList<<"Loans:";

    for(Loan &loan : player.getLoans()){
        loanItemList<<loan.getLoanName()+": $"+QString::number(loan.getAmount(), 'f', 2)+"     Minimum Payment: $"+QString::number(loan.getMinimum(), 'f', 2);
        ui->loanAccountBox->addItem(loan.getLoanName());
    }
    if(ui->loanAccountBox->count()==0){
        ui->payLoanButton->setEnabled(false);
    }
    else{
        ui->payLoanButton->setEnabled(true);
    }
    loanModelBox->setStringList(loanItemList);
    ui->listLoanView->setModel(loanModelBox);
}

void GameHome::drawRate(float rate, float minimumPayment){
    ui->rateAmountLabel->setText("%"+QString::number(rate, 'f', 4));
    ui->minimumPaymentLabel->setText("$"+QString::number(minimumPayment, 'f', 2));
    ui->loanButton->setEnabled(true);
}

void GameHome::calculateRate()
{
    emit sendLoanInfo(ui->loanAmountBox->value(),ui->loanLengthBox->currentText());
}

void GameHome::acceptLoan()
{
    //void acceptLoanModel(QString loanName, QString rateStr, QString lengthStr, int amount);
    emit acceptLoanModel(ui->loanNameBox->text(),ui->rateAmountLabel->text(),ui->loanLengthBox->currentText(),ui->loanAmountBox->value());
}

void GameHome::payLoan(){

    emit payLoanModel(ui->loanAccountBox->currentIndex(),ui->loanPayAmountBox->value(),ui->loanPayAccountBox->currentText());
}

void GameHome::drawAssetsTab(QList<Car> cars, QList<House> houses)
{

    // Sets the text of prices
    ui->carPriceLabel1->setText("Price: $" + QString::number(cars.value(0).getPrice(),'f', 2));
    ui->carPriceLabel2->setText("Price: $" + QString::number(cars.value(1).getPrice(), 'f', 2));
    ui->carPriceLabel3->setText("Price: $" + QString::number(cars.value(2).getPrice(), 'f', 2));
    ui->housePriceLabelLeft->setText("Price: $" + QString::number(houses.value(0).getPrice(), 'f', 2));
    ui->housePriceLabelMiddle->setText("Price: $" + QString::number(houses.value(1).getPrice(), 'f', 2));
    ui->housePriceLabelRight->setText("Price: $" + QString::number(houses.value(2).getPrice(), 'f', 2));
}

void GameHome::drawDate(int day)
{
    ui->date->setText("Day: " + QString::number(day));
    dayNum = day;
}

void GameHome::setCharts(QList<Stock> stocks)
{
    aaplPointSeries->append(dayNum, stocks.at(0).getPrice());
    aaplChart->removeSeries(aaplPointSeries);
    aaplChart->addSeries(aaplPointSeries);
    if(stocks.at(0).getPrice() > aaplAxisY->max())
    {
        aaplAxisY->setRange(0, stocks.at(0).getPrice());
    }

    googPointSeries->append(dayNum, stocks.at(2).getPrice());
    googChart->removeSeries(googPointSeries);
    googChart->addSeries(googPointSeries);
    if(stocks.at(2).getPrice() > googAxisY->max())
    {
        googAxisY->setRange(0, stocks.at(2).getPrice());
    }

    msftPointSeries->append(dayNum, stocks.at(1).getPrice());
    msftChart->removeSeries(msftPointSeries);
    msftChart->addSeries(msftPointSeries);
    if(stocks.at(1).getPrice() > msftAxisY->max())
    {
        msftAxisY->setRange(0, stocks.at(1).getPrice());
    }

    koPointSeries->append(dayNum, stocks.at(3).getPrice());
    koChart->removeSeries(koPointSeries);
    koChart->addSeries(koPointSeries);
    if(stocks.at(3).getPrice() > koAxisY->max())
    {
        koAxisY->setRange(0, stocks.at(3).getPrice());
    }

    metaPointSeries->append(dayNum, stocks.at(4).getPrice());
    metaChart->removeSeries(metaPointSeries);
    metaChart->addSeries(metaPointSeries);
    if(stocks.at(4).getPrice() > metaAxisY->max())
    {
        metaAxisY->setRange(0, stocks.at(4).getPrice());
    }

    xomPointSeries->append(dayNum, stocks.at(5).getPrice());
    xomChart->removeSeries(xomPointSeries);
    xomChart->addSeries(xomPointSeries);
    if(stocks.at(5).getPrice() > xomAxisY->max())
    {
        xomAxisY->setRange(0, stocks.at(5).getPrice());
    }

}

void GameHome::setStockPrices(QList<Stock> stocks){
    ui->stock1Price->setText(QString::number(stocks.at(0).getPrice()));
    if(stocks.at(0).getMarketHistory().back() > stocks.at(0).getPrice())
    {
        aaplPointSeries->setColor(Qt::red);
        ui->stock1Price->setStyleSheet("color: #FF0000;");
        ui->stock1PercentLabel->setStyleSheet("color: #FF0000;");
        ui->stock1PercentLabel->setText(QString::number((int)(((double)stocks.at(0).getPrice() - stocks.at(0).getMarketHistory().back())/stocks.at(0).getMarketHistory().back() * 100)) + "%");
    }
    else
    {
        aaplPointSeries->setColor(Qt::green);
        ui->stock1Price->setStyleSheet("color: #05FF00;");
        ui->stock1PercentLabel->setStyleSheet("color: #05FF00;");
        ui->stock1PercentLabel->setText("+" + QString::number((int)(((double)stocks.at(0).getPrice() - stocks.at(0).getMarketHistory().back())/stocks.at(0).getMarketHistory().back() * 100)) + "%");
    }
    ui->stock2Price->setText(QString::number(stocks.at(1).getPrice()));
    if(stocks.at(1).getMarketHistory().back() > stocks.at(1).getPrice())
    {
        msftPointSeries->setColor(Qt::red);
        ui->stock2Price->setStyleSheet("color: #FF0000;");
        ui->stock2PercentLabel->setStyleSheet("color: #FF0000;");
        ui->stock2PercentLabel->setText(QString::number((int)(((double)stocks.at(1).getPrice() - stocks.at(1).getMarketHistory().back())/stocks.at(1).getMarketHistory().back() * 100)) + "%");
    }
    else
    {
        msftPointSeries->setColor(Qt::green);
        ui->stock2Price->setStyleSheet("color: #05FF00;");
        ui->stock2PercentLabel->setStyleSheet("color: #05FF00;");
        ui->stock2PercentLabel->setText("+" + QString::number((int)(((double)stocks.at(1).getPrice() - stocks.at(1).getMarketHistory().back())/stocks.at(1).getMarketHistory().back() * 100)) + "%");
    }
    ui->stock3Price->setText(QString::number(stocks.at(2).getPrice()));
    if(stocks.at(2).getMarketHistory().back() > stocks.at(2).getPrice())
    {
        googPointSeries->setColor(Qt::red);
        ui->stock3Price->setStyleSheet("color: #FF0000;");
        ui->stock3PercentLabel->setStyleSheet("color: #FF0000;");
        ui->stock3PercentLabel->setText(QString::number((int)(((double)stocks.at(2).getPrice() - stocks.at(2).getMarketHistory().back())/stocks.at(2).getMarketHistory().back() * 100)) + "%");
    }
    else
    {
        googPointSeries->setColor(Qt::green);
        ui->stock3Price->setStyleSheet("color: #05FF00;");
        ui->stock3PercentLabel->setStyleSheet("color: #05FF00;");
        ui->stock3PercentLabel->setText("+" + QString::number((int)(((double)stocks.at(2).getPrice() - stocks.at(2).getMarketHistory().back())/stocks.at(2).getMarketHistory().back() * 100)) + "%");
    }
    ui->stock4Price->setText(QString::number(stocks.at(3).getPrice()));
    if(stocks.at(3).getMarketHistory().back() > stocks.at(3).getPrice())
    {
        koPointSeries->setColor(Qt::red);
        ui->stock4Price->setStyleSheet("color: #FF0000;");
        ui->stock4PercentLabel->setStyleSheet("color: #FF0000;");
        ui->stock4PercentLabel->setText(QString::number((int)(((double)stocks.at(3).getPrice() - stocks.at(3).getMarketHistory().back())/stocks.at(3).getMarketHistory().back() * 100)) + "%");
    }
    else
    {
        koPointSeries->setColor(Qt::green);
        ui->stock4Price->setStyleSheet("color: #05FF00;");
        ui->stock4PercentLabel->setStyleSheet("color: #05FF00;");
        ui->stock4PercentLabel->setText("+" + QString::number((int)(((double)stocks.at(3).getPrice() - stocks.at(3).getMarketHistory().back())/stocks.at(3).getMarketHistory().back() * 100)) + "%");
    }
    ui->stock5Price->setText(QString::number(stocks.at(4).getPrice()));
    if(stocks.at(4).getMarketHistory().back() > stocks.at(4).getPrice())
    {
        metaPointSeries->setColor(Qt::red);
        ui->stock5Price->setStyleSheet("color: #FF0000;");
        ui->stock5PercentLabel->setStyleSheet("color: #FF0000;");
        ui->stock5PercentLabel->setText(QString::number((int)(((double)stocks.at(4).getPrice() - stocks.at(4).getMarketHistory().back())/stocks.at(4).getMarketHistory().back() * 100)) + "%");
    }
    else
    {
        metaPointSeries->setColor(Qt::green);
        ui->stock5Price->setStyleSheet("color: #05FF00;");
        ui->stock5PercentLabel->setStyleSheet("color: #05FF00;");
        ui->stock5PercentLabel->setText("+" + QString::number((int)(((double)stocks.at(4).getPrice() - stocks.at(4).getMarketHistory().back())/stocks.at(4).getMarketHistory().back() * 100)) + "%");
    }
    ui->stock6Price->setText(QString::number(stocks.at(5).getPrice()));
    if(stocks.at(5).getMarketHistory().back() > stocks.at(5).getPrice())
    {
        xomPointSeries->setColor(Qt::red);
        ui->stock6Price->setStyleSheet("color: #FF0000;");
        ui->stock6PercentLabel->setStyleSheet("color: #FF0000;");
        ui->stock6PercentLabel->setText(QString::number((int)(((double)stocks.at(5).getPrice() - stocks.at(5).getMarketHistory().back())/stocks.at(5).getMarketHistory().back() * 100)) + "%");
    }
    else
    {
        xomPointSeries->setColor(Qt::green);
        ui->stock6Price->setStyleSheet("color: #05FF00;");
        ui->stock6PercentLabel->setStyleSheet("color: #05FF00;");
        ui->stock6PercentLabel->setText("+" + QString::number((int)(((double)stocks.at(5).getPrice() - stocks.at(5).getMarketHistory().back())/stocks.at(5).getMarketHistory().back() * 100)) + "%");
    }
}

void GameHome::setStockShareAmount(int stockIndex, int shareCount)
{
    switch(stockIndex)
    {
    case(0):
        ui->stock1SharesLabel->setText("Shares: " + QString::number(shareCount));
        break;
    case(1):
        ui->stock2SharesLabel->setText("Shares: " + QString::number(shareCount));
        break;
    case(2):
        ui->stock3SharesLabel->setText("Shares: " + QString::number(shareCount));
        break;
    case(3):
        ui->stock4SharesLabel->setText("Shares: " + QString::number(shareCount));
        break;
    case(4):
        ui->stock5SharesLabel->setText("Shares: " + QString::number(shareCount));
        break;
    case(5):
        ui->stock6SharesLabel->setText("Shares: " + QString::number(shareCount));
        break;
    }
}

void GameHome::setUpGame(int difficulty)
{
    emit setDifficulty(difficulty);
    emit getFullUi();
}

void GameHome::sellStock1Price()
{
    emit sellStockPrice(0);
}

void GameHome::sellStock2Price()
{
    emit sellStockPrice(1);
}

void GameHome::sellStock3Price()
{
    emit sellStockPrice(2);
}

void GameHome::sellStock4Price()
{
    emit sellStockPrice(3);
}

void GameHome::sellStock5Price()
{
    emit sellStockPrice(4);
}

void GameHome::sellStock6Price()
{
    emit sellStockPrice(5);
}

void GameHome::sendStock1Price()
{
    emit sendStockPrice(0);
}

void GameHome::sendStock2Price()
{
    emit sendStockPrice(1);
}

void GameHome::sendStock3Price()
{
    emit sendStockPrice(2);
}

void GameHome::sendStock4Price()
{
    emit sendStockPrice(3);
}

void GameHome::sendStock5Price()
{
    emit sendStockPrice(4);
}

void GameHome::sendStock6Price()
{
    emit sendStockPrice(5);
}

// sending car prices
void GameHome::sendLeftCarPrice()
{
    emit sendCarPrice(0);
}

void GameHome::sendMiddleCarPrice()
{
    emit sendCarPrice(1);
}

void GameHome::sendRightCarPrice()
{
    emit sendCarPrice(2);
}

// sending houes prices
void GameHome::sendLeftHousePrice()
{
    emit sendHousePrice(0);
}

void GameHome::sendMiddleHousePrice()
{
    emit sendHousePrice(1);
}

void GameHome::sendRightHousePrice()
{
    emit sendHousePrice(2);
}

void GameHome::cantAffordAsset(QString assetType)
{
    // need to find the label
    QLabel* cantAffordLabel = cantAfford.findChild<QLabel*>("assetText");
    // change it to the asset they were trying to buy
    cantAffordLabel->setText(assetType);
    // pop up and make them accept
    cantAfford.exec();
}

void GameHome::transferMoney()
{
    // grab the info from the UI
    double amount = ui->transferAmount->value();
    QString sendingAccount = ui->fromAccount->currentText();
    QString receivingAccount = ui->toAccount->currentText();
    ui->transferAmount->setValue(0.00);
    // this will send it to the model to calculate
    emit computeMoneyTransfer(amount, sendingAccount, receivingAccount);
}

void GameHome::changeCarObjectiveToGreen()
{
    // change the background of the label to green to show that it's done
    ui->objective1->setStyleSheet("background-color: green");
    // if we don't already know that it's done, we set it to done and up the objective done count
    if (!objective1Done)
    {
        objectivesCompleted++;
        objective1Done = true;
    }

    // check if we're ready to end the game
    if (objectivesCompleted >= 6)
        emit objectivesFinished();
}

void GameHome::changeHouseObjectiveToGreen()
{
    // change the background of the label to green to show that it's done
    ui->objective2->setStyleSheet("background-color: green");
    // if we don't already know that it's done, we set it to done and up the objective done count
    if (!objective2Done)
    {
        objectivesCompleted++;
        objective2Done = true;
    }
    // check if we're ready to end the game
    if (objectivesCompleted >= 6)
        emit objectivesFinished();
}

void GameHome::changeSavingsObjectiveToGreen()
{
    // change the background of the label to green to show that it's done
    ui->objective3->setStyleSheet("background-color: green");
    // if we don't already know that it's done, we set it to done and up the objective done count
    if (!objective3Done)
    {
        objectivesCompleted++;
        objective3Done = true;
    }
    // check if we're ready to end the game
    if (objectivesCompleted >= 6)
        emit objectivesFinished();
}

void GameHome::changeStocksObjectiveToGreen()
{
    // change the background of the label to green to show that it's done
    ui->objective4->setStyleSheet("background-color: green");
    // if we don't already know that it's done, we set it to done and up the objective done count
    if (!objective4Done)
    {
        objectivesCompleted++;
        objective4Done = true;
    }
    // check if we're ready to end the game
    if (objectivesCompleted >= 6)
        emit objectivesFinished();
}

void GameHome::changeNetWorthObjectiveToGreen()
{
    // change the background of the label to green to show that it's done
    ui->objective5->setStyleSheet("background-color: green");
    // if we don't already know that it's done, we set it to done and up the objective done count
    if (!objective5Done)
    {
        objectivesCompleted++;
        objective5Done = true;
    }
    // check if we're ready to end the game
    if (objectivesCompleted >= 6)
        emit objectivesFinished();
}

void GameHome::changeDebtFreeObjectiveToGreen()
{
    // change the background of the label to green to show that it's done
    ui->objective6->setStyleSheet("background-color: green");
    // if we don't already know that it's done, we set it to done and up the objective done count
    if (!objective6Done)
    {
        objectivesCompleted++;
        objective6Done = true;
    }
    // check if we're ready to end the game
    if (objectivesCompleted >= 6)
        emit objectivesFinished();
}

void GameHome::readyForCelebrate()
{
    // get the celebration drawing loop started
    celebration.updateDrawing();
    // hide the current so we can see the celebration
    this->hide();
    celebration.show();
}

void GameHome::displayTips()
{
    cantAffordAsset("Welcome to the financial literacy game! "
                    "\n The goal of this game is to complete all of your financial objectives"
                    "\n Scroll through the tab bar to see assets you can buy "
                    "\n as well as banking options which will help you reach your objectives!"
                    "\n The stock market may be the quickest way to earn money,"
                    "\n but can also lose you a lot of money if you are not careful."
                    "\n Buying a stock will give you one share of the  company, which "
                    "\n means you technically own a very small portion of the "
                    "\n company. When you buy a share, you can  then sell it"
                    "\n and either profit off of it or lose money if you bought"
                    "\n it at a higher price. Some tips for investing in the "
                    "\n stock market are to buy stocks when they are low,"
                    "\n and then sell them when they are higher. You also want "
                    "\n to diversify the stocks you buy as much as you can, so"
                    "\n if one stock fails you will not go bankrupt. You can also "
                    "\n watch for trends in the stocks, if they have recently "
                    "\n been gaining value, it is more likely they will gain more value "
                    "\n moving forward. Be careful though, as this is the same for stocks losing value");
}

void GameHome::displayLoanHelp(){
    cantAffordAsset("This is the Tab for aquiring loans which is crucial to beating the game."
                    "\n You can choose:"
                    "\n The name of the loan"
                    "\n The Amount of the loan"
                    "\n The Length of the loan"
                    "\n "
                    "\n Then pressing the calculate button will calculate the rate of the loan"
                    "\n based off the amount of assets that you have similiar to how in real life "
                    "\n the amount you earn and assets you put up for collateral will affect your  "
                    "\n eligibility for a loan."
                    "\n "
                    "\n Some things to keep in mind are that you must pay off your loan every month "
                    "\n or else the added interest amount will be much higher. In real life you will actually have"
                    "\n your credit score be affected which can decrease you likelihood of obtaining a loan. ");
}

