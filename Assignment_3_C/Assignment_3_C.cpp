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

    int first;
    int second;

    int validation;

    
    do {
        printf("Enter first transaction index to swap: ");
        validation = scanf_s("%lf", &first);
        getchar();

    } while (!isValidInput(validation));

    do {
        printf("Enter second transaction index to swap: ");
        validation = scanf_s("%lf", &first);
        getchar();

    } while (!isValidInput(validation));



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