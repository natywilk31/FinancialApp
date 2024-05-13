/// This is the header file for a loan.
/// It stores and maintains interest and the total amount.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#ifndef LOAN_H
#define LOAN_H
#include <QString>
class Loan
{
private:
    //The first day of the loan
    int dateStart;
    //Loan Length
    int loanLength;
    //Rate of loan
    float rate;
    //The last day of the loan
    int dateEnd;
    //Boolean of the loan has been paid that month
    bool monthlyPaid;
    //The amount on the loan
    float amount;
    //The minimum amount needed to be paid
    float minimum;
    //The loan name
    QString loanName;

public:
    Loan();
    /**
     * @brief Loan Constructor for creating a loan object within the game.
     * @param loanName The name of the loan.
     * @param amount The amount of the loan.
     * @param dateStart The first day the loan is pulled out.
     * @param loanLength The length of the loan in months.
     * @param rate The interest rate of the loan.
     */
    Loan(QString loanName, int amount, int dateStart, int loanLength, float rate);
    /**
     * @brief payLoan Pay the loan the amount and return any amount that is over the loan amount.
     * @param amountPaid The amount that is being paid to the loan.
     * @return The amount needed to be added to the players account.
     */
    float payLoan(int amountPaid);

    /**
     * @brief addInterest Add the interest to the loan
     */
    void addInterest();
    /**
     * @brief isPaid Checks wether the loan is paid off and returns the boolean
     * @return Boolean if paid
     */
    bool isPaid();
    /**
     * @brief getLoanName Returns loan name
     * @return Loan name
     */
    QString getLoanName();

    // getters
    float getAmount();
    float getMinimum();
};

#endif // LOAN_H
