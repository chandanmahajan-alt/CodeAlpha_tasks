#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BANK_FILE "bank_accounts.dat"
#define TRANSACTION_FILE "transactions.dat"
#define MAX_NAME 50
#define MAX_ACCOUNTS 100

// Structure for bank account
typedef struct {
    int account_no;
    char name[MAX_NAME];
    char account_type[20];
    double balance;
} BankAccount;

// Structure for transactions
typedef struct {
    int account_no;
    char transaction_type[20];
    double amount;
    char date[20];
    double balance_after;
} Transaction;

// Function declarations
void createAccount(void);
void depositMoney(void);
void withdrawMoney(void);
void checkBalance(void);
void displayAllAccounts(void);
void viewTransactionHistory(void);
int findAccountIndex(int account_no, BankAccount* accounts, int count);
void recordTransaction(int account_no, char* type, double amount, double balance);
void getCurrentDate(char* date);

int main() {
    int choice;

    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║   BANK ACCOUNT MANAGEMENT SYSTEM      ║\n");
    printf("║           CodeAlpha Mini Project       ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    while (1) {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Create New Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. View All Accounts\n");
        printf("6. View Transaction History\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                withdrawMoney();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                displayAllAccounts();
                break;
            case 6:
                viewTransactionHistory();
                break;
            case 7:
                printf("\n╔════════════════════════════════════════╗\n");
                printf("║  Thank you for using our Banking       ║\n");
                printf("║  Management System. Goodbye!           ║\n");
                printf("╚════════════════════════════════════════╝\n\n");
                exit(0);
            default:
                printf("\n✗ Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to get current date
void getCurrentDate(char* date) {
    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    strftime(date, 20, "%d/%m/%Y %H:%M", timeinfo);
}

// Function to create a new account
void createAccount(void) {
    FILE *file = fopen(BANK_FILE, "ab");
    if (file == NULL) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }

    BankAccount account;

    printf("\n════════════════════════════════════════\n");
    printf("        CREATE NEW ACCOUNT\n");
    printf("════════════════════════════════════════\n");

    printf("Enter Account Number: ");
    scanf("%d", &account.account_no);
    while (getchar() != '\n');

    printf("Enter Account Holder Name: ");
    fgets(account.name, MAX_NAME, stdin);
    account.name[strcspn(account.name, "\n")] = 0;

    printf("Enter Account Type (Savings/Checking/Business): ");
    fgets(account.account_type, 20, stdin);
    account.account_type[strcspn(account.account_type, "\n")] = 0;

    printf("Enter Initial Deposit Amount: ");
    scanf("%lf", &account.balance);

    fwrite(&account, sizeof(BankAccount), 1, file);
    fclose(file);

    char date[20];
    getCurrentDate(date);
    recordTransaction(account.account_no, "OPENING", account.balance, account.balance);

    printf("\n✓ Account created successfully!\n");
    printf("  Account Number: %d\n", account.account_no);
    printf("  Account Holder: %s\n", account.name);
    printf("  Account Type: %s\n", account.account_type);
    printf("  Initial Balance: Rs. %.2f\n", account.balance);
}

// Function to deposit money
void depositMoney(void) {
    FILE *file = fopen(BANK_FILE, "r+b");
    if (file == NULL) {
        printf("Error: Cannot open file!\n");
        return;
    }

    BankAccount account;
    BankAccount accounts[MAX_ACCOUNTS];
    int count = 0;
    int account_no;
    double deposit_amount;
    int found = 0;

    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        accounts[count++] = account;
    }
    fclose(file);

    printf("\n════════════════════════════════════════\n");
    printf("         DEPOSIT MONEY\n");
    printf("════════════════════════════════════════\n");
    printf("Enter Account Number: ");
    scanf("%d", &account_no);
    printf("Enter Deposit Amount: ");
    scanf("%lf", &deposit_amount);

    if (deposit_amount <= 0) {
        printf("\n✗ Invalid amount! Deposit amount must be positive.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (accounts[i].account_no == account_no) {
            found = 1;
            accounts[i].balance += deposit_amount;

            printf("\n✓ Deposit successful!\n");
            printf("  Account Holder: %s\n", accounts[i].name);
            printf("  Deposit Amount: Rs. %.2f\n", deposit_amount);
            printf("  New Balance: Rs. %.2f\n", accounts[i].balance);

            recordTransaction(account_no, "DEPOSIT", deposit_amount, accounts[i].balance);
            break;
        }
    }

    if (!found) {
        printf("\n✗ Account with number %d not found!\n", account_no);
        return;
    }

    file = fopen(BANK_FILE, "wb");
    if (file == NULL) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fwrite(&accounts[i], sizeof(BankAccount), 1, file);
    }
    fclose(file);
}

// Function to withdraw money
void withdrawMoney(void) {
    FILE *file = fopen(BANK_FILE, "r+b");
    if (file == NULL) {
        printf("Error: Cannot open file!\n");
        return;
    }

    BankAccount account;
    BankAccount accounts[MAX_ACCOUNTS];
    int count = 0;
    int account_no;
    double withdraw_amount;
    int found = 0;

    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        accounts[count++] = account;
    }
    fclose(file);

    printf("\n════════════════════════════════════════\n");
    printf("        WITHDRAW MONEY\n");
    printf("════════════════════════════════════════\n");
    printf("Enter Account Number: ");
    scanf("%d", &account_no);
    printf("Enter Withdrawal Amount: ");
    scanf("%lf", &withdraw_amount);

    if (withdraw_amount <= 0) {
        printf("\n✗ Invalid amount! Withdrawal amount must be positive.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (accounts[i].account_no == account_no) {
            found = 1;

            if (accounts[i].balance < withdraw_amount) {
                printf("\n✗ Insufficient balance!\n");
                printf("  Account Balance: Rs. %.2f\n", accounts[i].balance);
                printf("  Requested Withdrawal: Rs. %.2f\n", withdraw_amount);
                return;
            }

            accounts[i].balance -= withdraw_amount;

            printf("\n✓ Withdrawal successful!\n");
            printf("  Account Holder: %s\n", accounts[i].name);
            printf("  Withdrawal Amount: Rs. %.2f\n", withdraw_amount);
            printf("  Remaining Balance: Rs. %.2f\n", accounts[i].balance);

            recordTransaction(account_no, "WITHDRAWAL", withdraw_amount, accounts[i].balance);
            break;
        }
    }

    if (!found) {
        printf("\n✗ Account with number %d not found!\n", account_no);
        return;
    }

    file = fopen(BANK_FILE, "wb");
    if (file == NULL) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fwrite(&accounts[i], sizeof(BankAccount), 1, file);
    }
    fclose(file);
}

// Function to check balance
void checkBalance(void) {
    FILE *file = fopen(BANK_FILE, "rb");
    if (file == NULL) {
        printf("\nNo accounts found!\n");
        return;
    }

    BankAccount account;
    int account_no;
    int found = 0;

    printf("\n════════════════════════════════════════\n");
    printf("        CHECK BALANCE\n");
    printf("════════════════════════════════════════\n");
    printf("Enter Account Number: ");
    scanf("%d", &account_no);

    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        if (account.account_no == account_no) {
            found = 1;
            printf("\n✓ Account Details:\n");
            printf("────────────────────────────────────────\n");
            printf("Account Number: %d\n", account.account_no);
            printf("Account Holder: %s\n", account.name);
            printf("Account Type: %s\n", account.account_type);
            printf("Current Balance: Rs. %.2f\n", account.balance);
            printf("────────────────────────────────────────\n");
            break;
        }
    }

    if (!found) {
        printf("\n✗ Account with number %d not found!\n", account_no);
    }

    fclose(file);
}

// Function to display all accounts
void displayAllAccounts(void) {
    FILE *file = fopen(BANK_FILE, "rb");
    if (file == NULL) {
        printf("\nNo accounts found!\n");
        return;
    }

    BankAccount account;
    int count = 0;

    printf("\n════════════════════════════════════════\n");
    printf("       ALL BANK ACCOUNTS\n");
    printf("════════════════════════════════════════\n");
    printf("%-12s %-20s %-15s %-12s\n", "Acc. No", "Name", "Type", "Balance (Rs.)");
    printf("────────────────────────────────────────\n");

    while (fread(&account, sizeof(BankAccount), 1, file) == 1) {
        printf("%-12d %-20s %-15s %-12.2f\n",
               account.account_no, account.name, account.account_type, account.balance);
        count++;
    }

    printf("════════════════════════════════════════\n");
    printf("Total Accounts: %d\n", count);

    fclose(file);
}

// Function to record transactions
void recordTransaction(int account_no, char* type, double amount, double balance) {
    FILE *file = fopen(TRANSACTION_FILE, "ab");
    if (file == NULL) {
        printf("Warning: Cannot record transaction!\n");
        return;
    }

    Transaction trans;
    trans.account_no = account_no;
    strcpy(trans.transaction_type, type);
    trans.amount = amount;
    trans.balance_after = balance;
    getCurrentDate(trans.date);

    fwrite(&trans, sizeof(Transaction), 1, file);
    fclose(file);
}

// Function to view transaction history
void viewTransactionHistory(void) {
    FILE *file = fopen(TRANSACTION_FILE, "rb");
    if (file == NULL) {
        printf("\nNo transaction history found!\n");
        return;
    }

    Transaction trans;
    int account_no;
    int found = 0;

    printf("\n════════════════════════════════════════\n");
    printf("    TRANSACTION HISTORY\n");
    printf("════════════════════════════════════════\n");
    printf("Enter Account Number: ");
    scanf("%d", &account_no);

    printf("\nTransactions for Account %d:\n", account_no);
    printf("────────────────────────────────────────\n");
    printf("%-12s %-15s %-12s %-15s\n", "Type", "Amount", "Balance", "Date/Time");
    printf("────────────────────────────────────────\n");

    while (fread(&trans, sizeof(Transaction), 1, file) == 1) {
        if (trans.account_no == account_no) {
            found = 1;
            printf("%-12s %-15.2f %-12.2f %-15s\n",
                   trans.transaction_type, trans.amount, trans.balance_after, trans.date);
        }
    }

    if (!found) {
        printf("No transactions found for this account.\n");
    }
    printf("════════════════════════════════════════\n");

    fclose(file);


}
