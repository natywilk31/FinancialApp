/// This is the implementation  file for a loan.
/// It stores and maintains interest and the total amount.
/// Rowan Murdock, Jack Umina, Natalie Wilkins, Neeraja Vasa, Jesus Ponce
/// CS3505 Spring 2024 A9

#include "loan.h"
#include "qdebug.h"

Loan::Loan(){

}

Loan::Loan(QString loanName, int amount, int dateStart, int loanLength, float rate): dateStart(dateStart),
    loanLength(loanLength),rate(rate),amount(amount),loanName(loanName)
{
    float numPayments=loanLength;
    minimum=amount/numPayments;
    dateEnd=dateStart+(loanLength+30);
    monthlyPaid=true;
}

float Loan::getAmount(){
    return amount;
}

float Loan::getMinimum(){
    return minimum;
}
QString Loan::getLoanName(){
    return loanName;
}

float Loan::payLoan(int amountPaid)
{
    monthlyPaid=true;
    amount-=amountPaid;
    if(amount<0)
    {
        return -amount;
    }
    else
    {
        return 0.0;
    }
}
void Loan::addInterest()
{
    if (monthlyPaid)
    {
        amount+=(amount*(rate/100));
    }
    else
    {
        amount+=(amount*((rate/100)*2));
    }
    monthlyPaid=false;
}

bool Loan::isPaid()
{
    return (amount<=0);
}
