/*

CoinCount Pro Max Q Mega Plus Ultra
Author: Mackenzie Blackaby
Language: C
Description:
    Reads the data from coins.csv and allows the user to add new coins, read coins, view the total sum of all coins and update the database accordingly.
    These coins are collected for a charity organisation that collects loose change.
    If the organisation would like to withdraw coins from the money bank, then the program will detect the best way to withdraw this money.
Start Date: 29/10/2022
End Date: n/a

Code begins: 

*/
#include <stdlib.h>
#include <stdio.h>

#define introMessage "Welcome to CoinCount, the famous Coin Counter program from the 2020 GCSE NEA\nType 'Help' to get started\n"
#define helpMessage "\tCommand options:\n\n\tHelp: Show this help message\n\tAdd: add a specific coin to the database\n\tTotal: View total amount of money collected\n\tWithdraw: Withdraw a given amount of money, calculated in change\n\tExit: Save changes and exit the program\n\n\n"
#define coinTypes [1, 2, 5, 10, 20, 50, 100, 200]
#define csvSeparator ';'

typedef struct string{
    char contents[256];
} string;

int main(){
    int isRunning = 1;
    while(isRunning){

    }
    return 0;
}