#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 10
#define MAX_COL 10

// Function declarations
void inputMatrix(int matrix[MAX_ROW][MAX_COL], int rows, int cols);
void displayMatrix(int matrix[MAX_ROW][MAX_COL], int rows, int cols, char* name);
void addMatrices(int mat1[MAX_ROW][MAX_COL], int mat2[MAX_ROW][MAX_COL], 
                 int result[MAX_ROW][MAX_COL], int rows, int cols);
void multiplyMatrices(int mat1[MAX_ROW][MAX_COL], int mat2[MAX_ROW][MAX_COL], 
                      int result[MAX_ROW][MAX_COL], int rows1, int cols1, int cols2);
void transposeMatrix(int matrix[MAX_ROW][MAX_COL], int result[MAX_ROW][MAX_COL], 
                     int rows, int cols);

int main() {
    int matrix1[MAX_ROW][MAX_COL], matrix2[MAX_ROW][MAX_COL];
    int resultMatrix[MAX_ROW][MAX_COL];
    int rows1, cols1, rows2, cols2;
    int choice;
    
    printf("\n====================================\n");
    printf("   MATRIX OPERATIONS PROGRAM\n");
    printf("====================================\n\n");
    
    while (1) {
        printf("Select Operation:\n");
        printf("1. Matrix Addition\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Matrix Transpose\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1: {
                // Matrix Addition
                printf("\n--- MATRIX ADDITION ---\n");
                printf("Enter dimensions for both matrices (must be same):\n");
                printf("Enter rows: ");
                scanf("%d", &rows1);
                printf("Enter columns: ");
                scanf("%d", &cols1);
                
                if (rows1 <= 0 || rows1 > MAX_ROW || cols1 <= 0 || cols1 > MAX_COL) {
                    printf("Invalid dimensions! Max size is %dx%d\n", MAX_ROW, MAX_COL);
                    break;
                }
                
                printf("\nEnter Matrix 1:\n");
                inputMatrix(matrix1, rows1, cols1);
                
                printf("\nEnter Matrix 2:\n");
                inputMatrix(matrix2, rows1, cols1);
                
                addMatrices(matrix1, matrix2, resultMatrix, rows1, cols1);
                
                printf("\n");
                displayMatrix(matrix1, rows1, cols1, "Matrix 1");
                displayMatrix(matrix2, rows1, cols1, "Matrix 2");
                displayMatrix(resultMatrix, rows1, cols1, "Sum (Matrix 1 + Matrix 2)");
                break;
            }
            
            case 2: {
                // Matrix Multiplication
                printf("\n--- MATRIX MULTIPLICATION ---\n");
                printf("Enter dimensions for Matrix 1:\n");
                printf("Enter rows: ");
                scanf("%d", &rows1);
                printf("Enter columns: ");
                scanf("%d", &cols1);
                
                printf("\nFor Matrix 2, columns must equal Matrix 1's columns.\n");
                printf("Enter rows for Matrix 2: ");
                scanf("%d", &rows2);
                cols2 = cols1;
                
                if (rows1 <= 0 || rows1 > MAX_ROW || cols1 <= 0 || cols1 > MAX_COL ||
                    rows2 <= 0 || rows2 > MAX_ROW || cols2 <= 0 || cols2 > MAX_COL) {
                    printf("Invalid dimensions! Max size is %dx%d\n", MAX_ROW, MAX_COL);
                    break;
                }
                
                printf("\nEnter Matrix 1 (%dx%d):\n", rows1, cols1);
                inputMatrix(matrix1, rows1, cols1);
                
                printf("\nEnter Matrix 2 (%dx%d):\n", rows2, cols2);
                inputMatrix(matrix2, rows2, cols2);
                
                multiplyMatrices(matrix1, matrix2, resultMatrix, rows1, cols1, cols2);
                
                printf("\n");
                displayMatrix(matrix1, rows1, cols1, "Matrix 1");
                displayMatrix(matrix2, rows2, cols2, "Matrix 2");
                displayMatrix(resultMatrix, rows1, cols2, "Product (Matrix 1 x Matrix 2)");
                break;
            }
            
            case 3: {
                // Matrix Transpose
                printf("\n--- MATRIX TRANSPOSE ---\n");
                printf("Enter dimensions:\n");
                printf("Enter rows: ");
                scanf("%d", &rows1);
                printf("Enter columns: ");
                scanf("%d", &cols1);
                
                if (rows1 <= 0 || rows1 > MAX_ROW || cols1 <= 0 || cols1 > MAX_COL) {
                    printf("Invalid dimensions! Max size is %dx%d\n", MAX_ROW, MAX_COL);
                    break;
                }
                
                printf("\nEnter Matrix:\n");
                inputMatrix(matrix1, rows1, cols1);
                
                transposeMatrix(matrix1, resultMatrix, rows1, cols1);
                
                printf("\n");
                displayMatrix(matrix1, rows1, cols1, "Original Matrix");
                displayMatrix(resultMatrix, cols1, rows1, "Transpose");
                break;
            }
            
            case 4:
                printf("\nThank you for using Matrix Operations. Goodbye!\n");
                printf("====================================\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
        printf("\n------------------------------------\n\n");
    }
    
    return 0;
}

// Function to input matrix elements
void inputMatrix(int matrix[MAX_ROW][MAX_COL], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to display matrix
void displayMatrix(int matrix[MAX_ROW][MAX_COL], int rows, int cols, char* name) {
    printf("\n%s (%dx%d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%6d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to add two matrices
void addMatrices(int mat1[MAX_ROW][MAX_COL], int mat2[MAX_ROW][MAX_COL], 
                 int result[MAX_ROW][MAX_COL], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

// Function to multiply two matrices
void multiplyMatrices(int mat1[MAX_ROW][MAX_COL], int mat2[MAX_ROW][MAX_COL], 
                      int result[MAX_ROW][MAX_COL], int rows1, int cols1, int cols2) {
    // Initialize result matrix with zeros
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
        }
    }
    
    // Multiply matrices
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

// Function to transpose matrix
void transposeMatrix(int matrix[MAX_ROW][MAX_COL], int result[MAX_ROW][MAX_COL], 
                     int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}
