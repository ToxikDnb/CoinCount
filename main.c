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
#include <ctype.h>
#include <math.h>

//Defining macros (global variables)
#define introMessage "Welcome to CoinCount, the famous Coin Counter program from the 2020 GCSE NEA\nType 'Help' to get started\n"
#define helpMessage "\tCommand options:\n\n\tHelp: Show this help message\n\tAdd: add a specific coin to the database\n\tTotal: View total amount of money collected\n\tWithdraw: Withdraw a given amount of money, calculated in change\n\tSave: Save changes manually\n\tExit: Save changes and exit the program\n\n\n"
#define unknownCommandMessage "Unknown Command, please type 'help' for more information\n"
#define exitMessage "Thanks for choosing CoinCount, the famous Coin Counter program from the 2020 GCSE NEA!\n\n"
#define coinTypes (int[]){1, 2, 5, 10, 20, 50, 100, 200}
#define coinAmount 8
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
coinDB cdbConvert(string db);
void add(coinDB *data);
float total(coinDB *data);
void firstLineOf(string *str);
void toLower(string *str);
int isInList(string *str, int *array);
void writeContents(coinDB *data);
void withdraw(coinDB *data);


//Main function that runs when application is launched
int main(){
    int isRunning = 1;
    string command;
    string rawData = readContents();
    coinDB data = cdbConvert(rawData);
    printf(introMessage);
    while(isRunning){
        //Get input and apply filter functions
        printf(">> ");
        fgets(command.contents, stringSize, stdin);
        firstLineOf(&command);
        toLower(&command);
        printf("\n");
        //Command selector
        //Shows help menu
        if(!strcmp(command.contents, "help")){
            printf(helpMessage);
        }
        //Shows exit message and exits the program
        else if(!strcmp(command.contents, "exit")){
            printf(exitMessage);
            isRunning = 0;
        }
        else if(!strcmp(command.contents, "add")){
            add(&data);
        }
        else if(!strcmp(command.contents, "total")){
            float tot = total(&data);
            printf("The total amount of all coins is \x9c%.2f\n\n", tot);
        }
        else if(!strcmp(command.contents, "save")){
            writeContents(&data);
        }
        else if(!strcmp(command.contents, "withdraw")){
            withdraw(&data);
        }
        //If unknown command is entered
        else{
            printf(unknownCommandMessage);
        }
    }
    writeContents(&data);
    printf("Press enter to exit\n");
    fgetc(stdin);
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
    for(int i = 0; i < coinAmount; i++){
        data.contents[i] = 0;
    }
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

//Isolates the first line of a multi-line string
void firstLineOf(string *str){
    for(int i = 0; i < sizeof(str->contents)/sizeof(char); i++){
        if(str->contents[i] == '\n'){
            str->contents[i] = '\0';
            break;
        }
    }
}

//Makes all characters in a string lowercase
void toLower(string *str){
    int count = 0;
    while(str->contents[count] != '\0'){
        str->contents[count] = tolower(str->contents[count]);
        count++;
    }
}

//Checks if string item is in list of ints and returns position if found. -1 Indicates not found
int isInList(string *str, int *array){
    int result = -1;
    int item = atoi(str->contents);
    for(int i = 0; i < coinAmount; i++){
        if(item == array[i]){
            result = i;
            break;
        }
    }
    return result;
}

//Procedure for adding coins to total coins
void add(coinDB *data){
    int isInLoop = 1;
            printf("Please enter the coin type, in pence, to add. Allowed values are: ");
            for(int i = 0; i < coinAmount-1; i++){
                printf("%d, ", coinTypes[i]);
            }
            printf("& %d.\nType 0 to exit from loop\n", coinTypes[coinAmount-1]);
            string ans;
            do{
                printf(">> ");
                fgets(ans.contents, stringSize, stdin);
                firstLineOf(&ans);
                printf("\n");
                int pos = isInList(&ans, coinTypes);
                if(pos >= 0 && pos <= coinAmount){
                    data->contents[pos] += 1;
                }
                else if(!strcmp(ans.contents, "0")){
                    printf("Main Menu: \n\n");
                    isInLoop = 0;
                }
                else{
                    printf("Please try again!\n");
                }
                strcpy(ans.contents, "\0");
            } while(isInLoop);
}

//Procedure for getting total amount of coins
float total(coinDB *data){
    float totalPence = 0;
    for(int i = 0; i < coinAmount; i++){
        totalPence += data->contents[i] * coinTypes[i];
    }
    float totalPounds = totalPence/100;
    return totalPounds;
}

//Writes contents to coins.csv file
void writeContents(coinDB *data){
    string writtenString;
    writtenString = (string){.contents = ""};
    string curString = (string){.contents = ""};
    for(int i = 0; i < coinAmount-1; i++){
        snprintf(curString.contents, stringSize,"%d",data->contents[i]);
        strcat(writtenString.contents, strcat(curString.contents, ";"));
    }
    snprintf(curString.contents, stringSize,"%d",data->contents[coinAmount-1]);
    strcat(writtenString.contents, curString.contents);
    FILE *f = fopen(path, "w");
    fprintf(f, "%s", writtenString.contents);
    fclose(f);
}

//Procedure to copy one coinDB to another
void copyCoinDB(coinDB *destination, coinDB *source){
    for(int i = 0; i < coinAmount; i++){
        destination->contents[i] = source->contents[i];
    }
}

//Withdraws an amount from the moneybox, displays the best possible combination of coins to be taken out
void withdraw(coinDB *data){
    int tot = total(data)*100;
    string ans;
    printf("Please enter the amount you want to withdraw, in pence\n>> ");
    fgets(ans.contents, stringSize, stdin);
    printf("\n");
    int amount = atoi(ans.contents);
    float initAmount = amount;
    if(tot < amount){
        printf("You have not got enough money in your account to withdraw this amount.\n");
    }
    else{
        coinDB afterCoin;
        copyCoinDB(&afterCoin, data);
        string coins, tempString;
        strcpy(tempString.contents, "");
        strcpy(coins.contents, "");
        printf("The coins to withdraw this amount are: ");
        int change;
        for(int i = coinAmount-1; i >= 0; i--){
            change = 1;
            while(change){
                if(amount-coinTypes[i] >= 0 && afterCoin.contents[i] > 0){
                    afterCoin.contents[i] -= 1;
                    amount -= coinTypes[i];
                    if(coinTypes[i] >= 100){
                        strcat(coins.contents, "\x9c");
                        int p = coinTypes[i]/100;
                        sprintf(tempString.contents, "%d", p);
                        strcat(coins.contents, tempString.contents);
                    }
                    else{
                        sprintf(tempString.contents, "%d", coinTypes[i]);
                        strcat(coins.contents, tempString.contents);
                        strcat(coins.contents, "p");
                    }
                    strcat(coins.contents, ", ");
                }
                else{
                    change = 0;
                }
            }
            
        }
        if(amount == 0){
            printf("The coins to withdraw this amount are: %s which totals \x9c%.2f, which has now been withdrawn!\n", coins.contents, initAmount/100);
            copyCoinDB(data, &afterCoin);
            writeContents(data);
        }
        else{
            printf("The value you submitted is unable to be taken out with the coins that you have.\n");
        }
        
    }
}
