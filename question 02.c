#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_HISTORY 50

struct Transaction {
    char transactionDate[20];
    char transactionType[20];
    float transactionAmount;
};

struct BankAccount {
    char holderName[50];
    int accountNumber;
    char accountType[20];
    float accountBalance;
    char creationDate[20];
    char lastTransactionDate[20];
    struct Transaction history[MAX_HISTORY];
    int historyCount;
};

void createAccount(struct BankAccount arr[], int *total);
void depositAmount(struct BankAccount arr[], int total);
void withdrawAmount(struct BankAccount arr[], int total);
void showAccountDetails(struct BankAccount arr[], int total);
void showTransactionHistory(struct BankAccount arr[], int total);
float getMinimumBalance(char type[]);
float getInterestRate(char type[]);

int main() {
    struct BankAccount accounts[MAX_ACCOUNTS];
    int totalAccounts = 0;
    int menuChoice;

    do {
        printf("\n------ MENU ------\n");
        printf("1. Create new account\n");
        printf("2. Deposit amount\n");
        printf("3. Withdraw amount\n");
        printf("4. Show account details\n");
        printf("5. Show transaction history\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &menuChoice);

        if (menuChoice == 1)
            createAccount(accounts, &totalAccounts);

        else if (menuChoice == 2)
            depositAmount(accounts, totalAccounts);

        else if (menuChoice == 3)
            withdrawAmount(accounts, totalAccounts);

        else if (menuChoice == 4)
            showAccountDetails(accounts, totalAccounts);

        else if (menuChoice == 5)
            showTransactionHistory(accounts, totalAccounts);

    } while (menuChoice != 0);

    return 0;
}

float getMinimumBalance(char type[]) {
    if (strcmp(type, "Savings") == 0) return 1000;
    if (strcmp(type, "Current") == 0) return 5000;
    if (strcmp(type, "Fixed") == 0) return 10000;
    return 0;
}

float getInterestRate(char type[]) {
    if (strcmp(type, "Savings") == 0) return 4;
    if (strcmp(type, "Fixed") == 0) return 7;
    return 0;
}

void createAccount(struct BankAccount arr[], int *total) {
    int index = *total;

    printf("Enter account holder name: ");
    scanf("%s", arr[index].holderName);

    printf("Enter account number: ");
    scanf("%d", &arr[index].accountNumber);

    printf("Enter account type (Savings/Current/Fixed): ");
    scanf("%s", arr[index].accountType);

    float minBalance = getMinimumBalance(arr[index].accountType);
    arr[index].accountBalance = minBalance;

    printf("Enter account creation date (DD-MM-YYYY): ");
    scanf("%s", arr[index].creationDate);

    strcpy(arr[index].lastTransactionDate, arr[index].creationDate);

    arr[index].historyCount = 0;

    printf("Account created with minimum balance: %.2f\n", minBalance);

    *total = *total + 1;
}

void depositAmount(struct BankAccount arr[], int total) {
    int accNum;
    float amount;
    char date[20];

    printf("Enter account number: ");
    scanf("%d", &accNum);
int i;
    for ( i = 0; i < total; i++) {
        if (arr[i].accountNumber == accNum) {
            printf("Enter deposit amount: ");
            scanf("%f", &amount);

            printf("Enter date (DD-MM-YYYY): ");
            scanf("%s", date);

            arr[i].accountBalance += amount;

            strcpy(arr[i].lastTransactionDate, date);

            int h = arr[i].historyCount;
            arr[i].history[h].transactionAmount = amount;
            strcpy(arr[i].history[h].transactionType, "Deposit");
            strcpy(arr[i].history[h].transactionDate, date);
            arr[i].historyCount++;

            printf("Deposit successful. New Balance: %.2f\n", arr[i].accountBalance);
            return;
        }
    }

    printf("Account not found.\n");
}

void withdrawAmount(struct BankAccount arr[], int total) {
    int accNum;
    float amount;
    char date[20];

    printf("Enter account number: ");
    scanf("%d", &accNum);
int i,j;
    for ( i = 0; i < total; i++) {
        if (arr[i].accountNumber == accNum) {
            printf("Enter withdrawal amount: ");
            scanf("%f", &amount);

            float minBalance = getMinimumBalance(arr[i].accountType);

            if (arr[i].accountBalance - amount < minBalance) {
                printf("Withdrawal denied. Minimum balance for this account is %.2f\n", minBalance);
                return;
            }

            printf("Enter date (DD-MM-YYYY): ");
            scanf("%s", date);

            arr[i].accountBalance -= amount;
            strcpy(arr[i].lastTransactionDate, date);

            int h = arr[i].historyCount;
            arr[i].history[h].transactionAmount = amount;
            strcpy(arr[i].history[h].transactionType, "Withdrawal");
            strcpy(arr[i].history[h].transactionDate, date);
            arr[i].historyCount++;

            printf("Withdrawal successful. New Balance: %.2f\n", arr[i].accountBalance);
            return;
        }
    }

    printf("Account not found.\n");
}

void showAccountDetails(struct BankAccount arr[], int total) {
    int accNum;
    printf("Enter account number: ");
    scanf("%d", &accNum);
int i,j;
    for ( i = 0; i < total; i++) {
        if (arr[i].accountNumber == accNum) {
            printf("\nAccount Holder: %s\n", arr[i].holderName);
            printf("Account Number: %d\n", arr[i].accountNumber);
            printf("Account Type: %s\n", arr[i].accountType);
            printf("Balance: %.2f\n", arr[i].accountBalance);
            printf("Creation Date: %s\n", arr[i].creationDate);
            printf("Last Transaction Date: %s\n", arr[i].lastTransactionDate);
            printf("Interest Rate: %.2f%%\n", getInterestRate(arr[i].accountType));
            return;
        }
    }

    printf("Account not found.\n");
}

void showTransactionHistory(struct BankAccount arr[], int total) {
    int accNum;
    printf("Enter account number: ");
    scanf("%d", &accNum);
int i,j;
    for ( i = 0; i < total; i++) {
        if (arr[i].accountNumber == accNum) {
            printf("\nTransaction History:\n");
            for (j = 0; j < arr[i].historyCount; j++) {
                printf("%s | %s | %.2f\n",
                       arr[i].history[j].transactionDate,
                       arr[i].history[j].transactionType,
                       arr[i].history[j].transactionAmount);
            }
            return;
        }
    }

    printf("Account not found.\n");
}

