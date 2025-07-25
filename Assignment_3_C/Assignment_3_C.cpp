/*
* FILE : main.cpp
* PROJECT : SENG1070 - ASSIGNMENT 3 – ARRAY AND POINTER TECHNIQUES WITH BITWISE OPERATIONS
* PROGRAMMER : Mohammed Al-Fakih Student
* FIRST VERSION : 2025-07-24
* DESCRIPTION :
* A Cryptocurrency Wallet Manager
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>  
#include <iostream>

typedef struct Transaction {
    int data;
    struct Transaction* next;
} Transaction;

void display();
void printTransactions(Transaction* head);
void insertEnd(Transaction** head, int value);
Transaction* createNode(int value);
void addTransaction(Transaction* head);

int main(void)
{
    Transaction* head = NULL;
    int choice;
    bool exit = false;

    while (!exit) {
        display();
        printf("Enter choice: ");
        scanf_s("%d", &choice);
        getchar(); // consume newline

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
           
            break;
        }
        case 4: {
            break;
        }
        case 5: {
            break;
        }
        case 6: {
            break;
        }
        case 7: {
            break;
        }
        case 8: {
            exit = true;
            printf("\nThank you for using our Crypto Manager, see you soon!\n");
            break;
        }
        default:
            printf("\nInvalid option, please select a number between 1 and 8\n");
            break;
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

}

Transaction* createNode(int value) {
    Transaction* newNode = (Transaction*)malloc(sizeof(Transaction));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}
void addToList(Transaction** head, int value) {
    Transaction* newNode = createNode(value);
    if (*head == NULL) {   // Empty list
        *head = newNode;
        return;
    }
    Transaction* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

void printTransactions(Transaction* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void freeMemory(Transaction** head) {
    Transaction* temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
void addTransaction(Transaction* head) {

    
    int amount;
    bool stop = false;

    while (!stop) {
        printf("Enter transaction amount (-1 to stop): ");
        scanf_s("%d", &amount);
        getchar(); // consume newline

        if (amount < -1) {
            printf("Please enter a valid amount");
        }
        else if (amount == -1) {
            stop = true;
        }
        else {
            addToList(&head, amount);
        }
    }
}

