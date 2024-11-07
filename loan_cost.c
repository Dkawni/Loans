#include <stdio.h>
#include <math.h>

//This uses the formula for periodic payments to calculate the loan cost

int main() {

double amountBorrowed;
double interestRate;
int numPayments;
double monthlyPayments;
double totalPayment;
double loanCost;


printf("Please enter the amount of money you borrowed: $\n");
scanf("%lf", &amountBorrowed);

printf("Please enter the annual interest rate:\n");
scanf("%lf", &interestRate);

printf("Please enter the number of payments to be made:\n");
scanf("%d", &numPayments);

double periodicPaymentDenom = 1 - pow((1+interestRate/12), -numPayments); //formula for periodic payment denominator
monthlyPayments =(amountBorrowed*interestRate/12)/periodicPaymentDenom; //use it to calculate the rest of the equation

totalPayment = monthlyPayments * numPayments; //calculate each month and multiply it by the total payments
loanCost = totalPayment - amountBorrowed; //how much user actually paid for the loan

printf("A loan of $%.2lf with an annual interest of %.2lf paid off over %d months will have monthly payments of $%.2lf.\n", amountBorrowed, interestRate, numPayments, monthlyPayments);

printf("In total, you will pay $%.2lf, making the cost of your loan $%.2lf.\n", totalPayment, loanCost);
}