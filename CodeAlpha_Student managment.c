#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "student_records.dat"
#define MAX_NAME 50
#define MAX_STUDENTS 100

// Structure to store student data
typedef struct {
    int roll_no;
    char name[MAX_NAME];
    float gpa;
    char branch[MAX_NAME];
} Student;

// Function declarations
void addStudent(void);
void deleteStudent(void);
void updateStudent(void);
void searchStudent(void);
void displayAllStudents(void);
void loadStudentsFromFile(Student* students, int* count);
void saveStudentsToFile(Student* students, int count);

int main() {
    int choice;

    printf("\n========================================\n");
    printf("  STUDENT MANAGMENT SYSTEM\n");
    printf("========================================\n\n");

    while (1) {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Add Student Record\n");
        printf("2. Delete Student Record\n");
        printf("3. Update Student Record\n");
        printf("4. Search Student Record\n");
        printf("5. Display All Records\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                displayAllStudents();
                break;
            case 6:
                printf("\nThank you for using Student Managment System. Goodbye!\n");
                printf("========================================\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to add a new student
void addStudent(void) {
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }

    Student student;

    printf("\n--- ADD NEW STUDENT ---\n");
    printf("Enter Roll Number: ");
    scanf("%d", &student.roll_no);
    while (getchar() != '\n');

    printf("Enter Student Name: ");
    fgets(student.name, MAX_NAME, stdin);
    student.name[strcspn(student.name, "\n")] = 0;

    printf("Enter Branch: ");
    fgets(student.branch, MAX_NAME, stdin);
    student.branch[strcspn(student.branch, "\n")] = 0;

    printf("Enter GPA: ");
    scanf("%f", &student.gpa);

    fwrite(&student, sizeof(Student), 1, file);
    fclose(file);

    printf("\n✓ Student record added successfully!\n");
}

// Function to delete a student record
void deleteStudent(void) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    Student student;
    Student students[MAX_STUDENTS];
    int count = 0;
    int roll_to_delete, found = 0;

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        students[count++] = student;
    }
    fclose(file);

    printf("\n--- DELETE STUDENT ---\n");
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll_to_delete);

    file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (students[i].roll_no == roll_to_delete) {
            found = 1;
            printf("\n✓ Student record deleted successfully!\n");
        } else {
            fwrite(&students[i], sizeof(Student), 1, file);
        }
    }

    fclose(file);

    if (!found) {
        printf("\n✗ Student with Roll Number %d not found!\n", roll_to_delete);
    }
}

// Function to update a student record
void updateStudent(void) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    Student student;
    Student students[MAX_STUDENTS];
    int count = 0;
    int roll_to_update, found = 0;

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        students[count++] = student;
    }
    fclose(file);

    printf("\n--- UPDATE STUDENT ---\n");
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll_to_update);
    while (getchar() != '\n');

    for (int i = 0; i < count; i++) {
        if (students[i].roll_no == roll_to_update) {
            found = 1;
            printf("\nCurrent Details:\n");
            printf("Name: %s\n", students[i].name);
            printf("Branch: %s\n", students[i].branch);
            printf("GPA: %.2f\n", students[i].gpa);

            printf("\nEnter new details:\n");
            printf("Enter Name: ");
            fgets(students[i].name, MAX_NAME, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            printf("Enter Branch: ");
            fgets(students[i].branch, MAX_NAME, stdin);
            students[i].branch[strcspn(students[i].branch, "\n")] = 0;

            printf("Enter GPA: ");
            scanf("%f", &students[i].gpa);

            printf("\n✓ Student record updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("\n✗ Student with Roll Number %d not found!\n", roll_to_update);
        return;
    }

    file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error: Cannot open file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fwrite(&students[i], sizeof(Student), 1, file);
    }
    fclose(file);
}

// Function to search for a student
void searchStudent(void) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    Student student;
    int roll_to_search, found = 0;

    printf("\n--- SEARCH STUDENT ---\n");
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll_to_search);

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        if (student.roll_no == roll_to_search) {
            found = 1;
            printf("\n✓ Student Found!\n");
            printf("----------------------------------------\n");
            printf("Roll Number: %d\n", student.roll_no);
            printf("Name: %s\n", student.name);
            printf("Branch: %s\n", student.branch);
            printf("GPA: %.2f\n", student.gpa);
            printf("----------------------------------------\n");
            break;
        }
    }

    if (!found) {
        printf("\n✗ Student with Roll Number %d not found!\n", roll_to_search);
    }

    fclose(file);
}

// Function to display all student records
void displayAllStudents(void) {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    Student student;
    int count = 0;

    printf("\n--- ALL STUDENT RECORDS ---\n");
    printf("========================================\n");
    printf("%-8s %-20s %-15s %-8s\n", "Roll No", "Name", "Branch", "GPA");
    printf("========================================\n");

    while (fread(&student, sizeof(Student), 1, file) == 1) {
        printf("%-8d %-20s %-15s %-8.2f\n",
               student.roll_no, student.name, student.branch, student.gpa);
        count++;
    }

    printf("========================================\n");
    printf("Total Records: %d\n", count);

    fclose(file);
}

