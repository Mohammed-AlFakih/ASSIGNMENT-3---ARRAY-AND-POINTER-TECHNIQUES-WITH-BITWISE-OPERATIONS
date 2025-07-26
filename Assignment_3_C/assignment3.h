#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H

typedef struct Transaction {
    double amount;
    unsigned char flags;
    struct Transaction* next;
} Transaction;

void display(void);
void printTransactions(Transaction* head);
void addToList(Transaction** head, double value);
void addTransaction(Transaction** head);
void calculateTransactions(Transaction* head);
void freeMemory(Transaction** head);
void transactionFee(Transaction* head);
void findHighest(Transaction* head);
void swapTransactions(Transaction* head);
void maskTransactions(Transaction* head);
Transaction* createNode(double value);
int isValidInput(int x);

#endif