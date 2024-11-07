#include <stdio.h>
/*
This program takes values and calculates the users retirement fund either after paying off loans
or while paying off loans
*/

double LoanAndInvest(double loanPayment, double annualIntRate, double minMonthLoanPay, double moneyForLR, double investAnnReturn, int currAge, int retireAge) {
    /*
    This function calculates paying off the loan and investing at the same time
    @investmentBalance = the money you have in your retirement account
    @monthIntRate = the monthly loan interest rate that applies every month
    @monthInvestRate = the monthly interest rate that applies every month to the retirement account
    @monthsUntilRetirement = calculates the months before retirement of the user
    */
    double investmentBalance = 0.0;
    double monthIntRate = annualIntRate / 12;
    double monthInvestRate = investAnnReturn / 12;
    int monthsUntilRetirement = (retireAge - currAge) * 12;

    for (int i = 0; i < monthsUntilRetirement; ++i){ //puts intereset on the loan and retirement count each month
        loanPayment = loanPayment * (1 + monthIntRate);
        investmentBalance = investmentBalance * (1 + monthInvestRate); //puts interest into the reitrement account

        if (loanPayment <= minMonthLoanPay) { //if the loan payment is less than how much you pay per month
            minMonthLoanPay = loanPayment; //makes the minimum payment the rest of the loan payment
        }
        loanPayment = loanPayment - minMonthLoanPay; //pays off the rest of the loan
        
        double investAmount = moneyForLR - minMonthLoanPay; //puts the rest of the money after paying off the loan into the investment balance
        investmentBalance = investmentBalance + investAmount;
    }

    investmentBalance = investmentBalance - loanPayment; //subtracts the total balance calcualted from the loan payment
    //checks to see if the loan was paid off
    return investmentBalance;
}

double LoanBeforeInvest(double loanPayment, double annualIntRate, double minMonthLoanPay, double moneyForLR, double investAnnReturn, int currAge, int retireAge) {
    /*
    This function calculates paying off the loan first and then investing
    @newMoneyForLR = the rest of the payment for the month is the loan is smaller than the max money to put into the account
    @investmentBalance = the money in the investment account
    @monthsUntilRetirement = the amount of months before the user retires
    @monthIntRate = the monthly interest rate on the loan
    @monthInvestRate = the interest rate on the retirement account each month
    */
    double newMoneyForLR;
    double investmentBalance = 0.0;
    int monthsUntilRetirement = (retireAge - currAge) * 12;
    double monthIntRate = annualIntRate / 12;
    double monthInvestRate = investAnnReturn / 12;

    for (int i = 0; i < monthsUntilRetirement; ++i) { //run until the retired age
        investmentBalance = investmentBalance * (1 + monthInvestRate);
        loanPayment = loanPayment * (1 + monthIntRate);
        if (loanPayment >= moneyForLR) { //subtracts all the money from the loan when the payment is greater than the max amount of money the user puts in every month
            loanPayment = loanPayment - moneyForLR;

        } else if (loanPayment == 0) { //adds to the investment balance when the loan payment is finished
            investmentBalance = investmentBalance + moneyForLR;

        }  else if (loanPayment < moneyForLR) { //pays the rest of the loan off
            newMoneyForLR = loanPayment;
            loanPayment = loanPayment - newMoneyForLR;
            investmentBalance += moneyForLR - newMoneyForLR;
        }
    }
    investmentBalance = investmentBalance - loanPayment; //subtracts the total balance calcualted from the loan payment. 
    //checks to see if the loan was paid off
    return investmentBalance;
}

int main() {
    /*
    This function continuously asks the user for responses until they give the valid ones
    @loanPayment = the amount in the loan
    @annualIntRate = the yearly interest rate on the loan
    @minMonthLoanPay = the minimum loan payment each month
    @moneyForLR = The max amount of money each month the user will put into loans or retirement
    @currAge = the current age of the user
    @retireAge = the age the user wants to retire at
    @investAnnReturn = the interest on the retirement account each year
    */
    double loanPayment, annualIntRate, minMonthLoanPay, moneyForLR, currAge, retireAge, investAnnReturn;
   
   do{

    printf("Enter how much you owe in loans: ");
    scanf("%lf", &loanPayment);

   } while (loanPayment < 0);
      
   do{ 

    printf("Enter the annual interest rate of the loans: ");
    scanf("%lf", &annualIntRate);

   } while (annualIntRate < 0);

    do {

    printf("Enter your minimum monthly loan payment: ");
    scanf("%lf", &minMonthLoanPay);

    } while (minMonthLoanPay < 0);

    do {

    printf("Enter how much money you will be putting towards loans/retirement each month: ");
    scanf("%lf", &moneyForLR);

    } while (moneyForLR < minMonthLoanPay);

    do {

    printf("Enter your current age: ");
    scanf("%lf", &currAge);

    } while (currAge < 0);

   do {

    printf("Enter the age you plan to retire at: ");
    scanf("%lf", &retireAge);
   } while (retireAge < currAge);

    do {

    printf("Enter your predicted annual rate of return: ");
    scanf("%lf", &investAnnReturn);

    }while (investAnnReturn < 0);

    double loanAndInvest = LoanAndInvest (loanPayment, annualIntRate, minMonthLoanPay, moneyForLR, investAnnReturn, currAge, retireAge);
    double loanBeforeInvest = LoanBeforeInvest(loanPayment, annualIntRate, minMonthLoanPay, moneyForLR, investAnnReturn, currAge, retireAge);

    if (loanAndInvest >= loanBeforeInvest) { //compares the money and sees which one is bigger to recommend to the user
        printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n");
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you paid off your loan before investing.", loanAndInvest, loanBeforeInvest);
    } else {
        printf("You should apply all $%.2lf towards your loan before making any investments.\n", moneyForLR);
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you only made minimum payments.", loanBeforeInvest, loanAndInvest);
    }

}