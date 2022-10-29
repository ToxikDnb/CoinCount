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
#include <string.h>

//Defining macros (global variables)
#define introMessage "Welcome to CoinCount, the famous Coin Counter program from the 2020 GCSE NEA\nType 'Help' to get started\n"
#define helpMessage "\tCommand options:\n\n\tHelp: Show this help message\n\tAdd: add a specific coin to the database\n\tTotal: View total amount of money collected\n\tWithdraw: Withdraw a given amount of money, calculated in change\n\tExit: Save changes and exit the program\n\n\n"
#define coinTypes (int[]){1, 2, 5, 10, 20, 50, 100, 200}
#define csvSeparator ';'
#define path "coins.csv"
#define stringSize 256

//Define string type for ease of use
typedef struct string{
    char contents[stringSize];
} string;

//Define coinHolder type to store coin information
typedef struct coinDB{
    int contents[sizeof(coinTypes)/sizeof(coinTypes[0])];
} coinDB;

//Pre-define function names
string readContents();
coinDB cdbConvert();
string remNewline();

//Main function that runs when application is launched
int main(){
    int isRunning = 1;
    string command;
    string rawData = readContents();
    coinDB data = cdbConvert(rawData);
    printf(introMessage);
    while(isRunning){
        printf(">> ");
        fgets(command.contents, stringSize, stdin);
        printf("\n");

    }
    return 0;
}

//Opens the file in read mode and returns a string containing the contents of the file
string readContents(){
    FILE *file = fopen(path, "r");
    rewind(file);
    string contents;
    fgets(contents.contents, stringSize, file);
    fclose(file);
    return contents;
}

//Converts contents of file into coinDB structure
coinDB cdbConvert(string db){
    coinDB data;
    char cChar;
    string cStr;
    int characterCount = 0, dataCount = 0, stringCount = 0;
    while(cChar != '\0'){
        cChar = db.contents[characterCount];
        if(cChar == csvSeparator){
            data.contents[dataCount] = atoi(cStr.contents);
            dataCount++;
            stringCount = 0;
            strcpy(cStr.contents, "");
        }
        else{
            cStr.contents[stringCount] = cChar;
            stringCount++;
        }
        characterCount++;
    }
    return data;
}