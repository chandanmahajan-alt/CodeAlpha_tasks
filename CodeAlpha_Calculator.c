#include <stdio.h>
#include <stdlib.h>

// Function declarations
float add(float a, float b);
float subtract(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);

int main() {
    float num1, num2, result;
    char operator;
    int choice;

    printf("\n=================================\n");
    printf("   BASIC CALCULATOR PROGRAM\n");
    printf("=================================\n\n");

    while (1) {
        printf("Enter first number: ");
        if (scanf("%f", &num1) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Enter second number: ");
        if (scanf("%f", &num2) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("\nSelect operation:\n");
        printf("1. Addition (+)\n");
        printf("2. Subtraction (-)\n");
        printf("3. Multiplication (*)\n");
        printf("4. Division (/)\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                result = add(num1, num2);
                printf("\n%.2f + %.2f = %.2f\n", num1, num2, result);
                break;

            case 2:
                result = subtract(num1, num2);
                printf("\n%.2f - %.2f = %.2f\n", num1, num2, result);
                break;

            case 3:
                result = multiply(num1, num2);
                printf("\n%.2f * %.2f = %.2f\n", num1, num2, result);
                break;

            case 4:
                if (num2 == 0) {
                    printf("\nError: Division by zero is not allowed!\n");
                } else {
                    result = divide(num1, num2);
                    printf("\n%.2f / %.2f = %.2f\n", num1, num2, result);
                }
                break;

            case 5:
                printf("\nThank you for using the calculator. Goodbye!\n");
                printf("=================================\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please enter a number between 1 and 5.\n");
        }

        printf("\n---------------------------------\n\n");
    }

    return 0;
}

// Function to add two numbers
float add(float a, float b) {
    return a + b;
}

// Function to subtract two numbers
float subtract(float a, float b) {
    return a - b;
}

// Function to multiply two numbers
float multiply(float a, float b) {
    return a * b;
}

// Function to divide two numbers
float divide(float a, float b) {
    return a / b;
}
