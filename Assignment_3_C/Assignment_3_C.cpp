/*
* FILE : main.cpp
* PROJECT : SENG1070 - ASSIGNMENT 3 – ARRAY AND POINTER TECHNIQUES WITH BITWISE OPERATIONS
* PROGRAMMER : Mohammed Al-Fakih Student
* FIRST VERSION : 2025-07-24
* DESCRIPTION :
* A Cryptocurrency Wallet Manager
*/

#define FLAG_PROCESSED 0x01  
#define FLAG_REFUNDED  0x02

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>  
#include <iostream>

typedef struct Transaction {
    double amount;
    unsigned char flags;
    struct Transaction* next;
} Transaction;

void display();
void printTransactions(Transaction* head);
void addToList(Transaction** head, double value);
void addTransaction(Transaction** head);
void calculateTransactions(Transaction* head);
void freeMemory(Transaction** head);
void transactionFee(Transaction* head);
void findHighest(Transaction* head);
void swapTransactions(Transaction* head);
Transaction* createNode(double value);
int isValidInput(int x);

int main(void)
{
    Transaction* head = NULL;
    int choice;
    bool exit = false;
    int validation;

    while (!exit) {
        display();
        printf("Enter choice: ");
        validation = scanf_s("%d", &choice);
        getchar();

        if (isValidInput(validation)) {
            switch (choice) {
            case 1: {
                addTransaction(&head);
                break;
            }
            case 2: {
                printTransactions(head);
                break;
            }
            case 3: {
                transactionFee(head);
                break;
            }
            case 4: {
                findHighest(head);
                break;
            }
            case 5: {
                swapTransactions(head);
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                calculateTransactions(head);
                break;
            }
            case 8: {
                exit = true;
                //freeMemory(&head);
                printf("\nThank you for using our Crypto Manager, see you soon!\n");
                break;
            }
            default:
                printf("\nInvalid option, please select a number between 1 and 8\n");
                break;
            }
        }
    }
}

void display() {

    printf("\n1. Add Transaction\n");
    printf("2. Display Transactions\n");
    printf("3. Apply Transaction Fees\n");
    printf("4. Find Highest Transaction\n");
    printf("5. Swap Transactions\n");
    printf("6. Manage Flags\n");
    printf("7. Calculate Total and Average\n");
    printf("8. Exit\n");
    return;
}

Transaction* createNode(double value) {
    Transaction* newNode = (Transaction*)malloc(sizeof(Transaction));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->amount = value;    // Set transaction amount
    newNode->flags = 0;          
    newNode->next = NULL;
    return newNode;
}
void addToList(Transaction** head, double value) {
    Transaction* newNode = createNode(value);
    if (*head == NULL) {   // Empty list
        *head = newNode;
        return;
    }
    Transaction* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;

    return;
}

void printTransactions(Transaction* head) {

    int transactionsNum = 1;
    if (head == NULL) {
        printf("No transactions found.\n");
        return;
    }

    printf("\nTransactions: \n");

    while (head != NULL) {
        printf("Transaction %i: $%.2f, Processed: %s, Refunded: %s\n", 
            transactionsNum,
            head->amount, 
            (head->flags & FLAG_PROCESSED) ? "Yes" : "No",
            (head->flags & FLAG_REFUNDED) ? "Yes" : "No");

        head = head->next;
        transactionsNum++;
    }
    return;
}

void freeMemory(Transaction** head) {

    Transaction* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    return;
}
void addTransaction(Transaction** head) {

    double amount;
    bool stop = false;
    int validation;

    while (!stop) {
        printf("Enter transaction amount (-1 to stop): ");
        validation = scanf_s("%lf", &amount);
        getchar();
        // scanf_s return 1 if it is an integer. However, if the user
        // entered a letter, it returns 0, therefore, I used it to check for 
        // user input validation, I used isValidInput to print a message if
        // user input is invalid (a letter)
        if (isValidInput(validation)) {
           
            if (amount < -1) {
                printf("\nPlease enter a valid amount\n");
            }
            else if (amount == -1) {
                stop = true;
            }
            else {
                addToList(head, amount);
            }
        }

    }

    return;
}


void calculateTransactions(Transaction* head) {

    if (head == NULL) {
        printf("No transactions to calculate yet!\n");
        return;
    }

    double total = 0.0;
    int transactions = 0;

    // If there is a transaction, then calculate amount and 
    // calculate how many transactions are there
    while (head != NULL) {
        total += head->amount;
        head = head->next;
        transactions++;
    }

    // If there is a transaction, calculate average by dividing 
    // total of transactions by how many transactions are there, basic math I mean (:
    if (transactions != 0) {
        double average;
        average = total / transactions;
        printf("\nTotal Transaction Amount: $%.2f", total);
        printf("\nAverage Transaction Value: $%.2f\n", average);

    }
 

    return;
}

void transactionFee(Transaction* head) {

    if (head == NULL) {
        printf("No transactions to process yet!\n");
        return;
    }

    Transaction* transactions = head;
    double percentage;
    int validation;

    do {
            printf("Enter fee percentage: ");
            validation = scanf_s("%lf", &percentage);
            getchar();

            if ((percentage < 0 || percentage > 100)) {
                printf("Please enter a valid positive percentage, and no fee percentage above 100\n\n");
            }
        } while ((percentage < 0 || percentage > 100) || (!isValidInput(validation)));

   
    percentage /= 100;
    
    while (head != NULL) {

        double deduct = head->amount * percentage;
        head->amount -= deduct;
        head = head->next;
    }

    printf("\nUpdated transactions after deduction:\n");
    printTransactions(transactions);
    return;
}

void findHighest(Transaction* head) {
    
    if (head == NULL) {
        printf("No transactions to find highest value yet!\n");
        return;
    }

    double highest = head->amount;

    while (head != NULL) {
        
        if (highest < head->amount) {
            highest = head->amount;
        }
        head = head->next;
    }

    printf("Highest transaction amount: $%.2f\n", highest);
    return;
}

void swapTransactions(Transaction* head) {

    if (head == NULL) {
        printf("No transactions to swap yet!\n");
        return;
    }

    int maxTransactions = 0;
    int minTransactions = 1;

    int first;
    int second;

    int validation1;
    int validation2;

    bool stop = false;

    Transaction* temp1 = head;
    Transaction* temp2 = head;

    Transaction* swap1 = head;
    Transaction* swap2 = head;

    while (head != NULL) {
        maxTransactions++;
        head = head->next;
    }

    if (maxTransactions <= 1) {
        printf("Insufficient number of transaction to swap\n\n");
        return;
    }

    do {

        do {
            printf("Enter first transaction index to swap: ");
            validation1 = scanf_s("%i", &first);
            getchar();

            if ((first > maxTransactions) || (first < minTransactions)) {
                printf("Invalid index, please enter a positive index and within the number of transactions\n\n");
            }
            else {
                stop = true;
            }

        } while (!isValidInput(validation1) || !stop);

        do {
            printf("Enter second transaction index to swap: ");
            validation2 = scanf_s("%i", &second);
            getchar();

            if (second > maxTransactions || second < minTransactions) {
                printf("Invalid index, please enter a positive index and within the number of transactions\n\n");
                stop = false;
            }
            else {
                stop = true;
            }

        } while (!isValidInput(validation2) || !stop);

    } while (!stop);



    double number1 = 0;
    double number2 = 0;


    // Traverse through dynamic linked list to find
    // the value with specified index, the first number to swap.
    for (int i = 1; i < first; i++) {
        temp1 = temp1->next;
    }
    number1 = temp1->amount;

    // Traverse through dynamic linked list to find
    // the value with specified index, the second number to swap.
    for (int i = 1; i < second; i++) {
        temp2 = temp2->next;
    }
    number2 = temp2->amount;


    // I solved the problem by storing the decimal difference.
    // Since XOR only does not support swapping floating numbers, I stored
    // the original number in variables called (decimal1, decimal2). Since casting
    // (int) for the numbers to swap, the decimals will be lost. There for, we can
    // add them after this change since we stored them in (decimal1, decimal2).
    
    // Example: number1 = $2.50, number2 = $5.75. 
    // After casting and swapping, they will be: number1 = $5.00, number2 = $2.00.
    // Now, we take the difference by: decimal1 - number2 (because they swapped values)
    // which means: $2.50 - $2.00 = $0.50.
    // And: decimal2 = decimal2 - number1, -> ($5.75 - $5.00 = $0.75).
    // Now, number1 += decimal2 = $5.00 + $0.75 = $5.75.
    // And: number2 += decimal1 = $2.00 + $0.50 = $2.50.
    double decimal1 = number1;
    double decimal2 = number2;

    number1 = (int)number1 ^ (int)number2;
    number2 = (int)number1 ^ (int)number2;
    number1 = (int)number1 ^ (int)number2;

    decimal1 = decimal1 - number2;
    decimal2 = decimal2 - number1;

    number1 += decimal2;
    number2 += decimal1;

    // Update the values in transactions list
    temp1->amount = number1;
    temp2->amount = number2;

    printf("\nSwapping was successful!\n\n");

    return;
}

int isValidInput(int validation) {

    if (validation != 1) {
        printf("Invalid input, please enter a number.\n");
        return 0;
    }
    else {
        return 1;
    }
}