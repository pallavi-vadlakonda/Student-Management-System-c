#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILENAME "students.dat"

typedef struct {
    int id;
    char name[50];
    int age;
    float gpa;
} Student;

Student students[MAX_STUDENTS];
int num_students = 0;

void loadStudents() {
    FILE *file = fopen(FILENAME, "rb");
    if (file) {
        fread(&num_students, sizeof(int), 1, file);
        fread(students, sizeof(Student), num_students, file);
        fclose(file);
    }
}

void saveStudents() {
    FILE *file = fopen(FILENAME, "wb");
    if (file) {
        fwrite(&num_students, sizeof(int), 1, file);
        fwrite(students, sizeof(Student), num_students, file);
        fclose(file);
    }
}

void addStudent() {
    if (num_students >= MAX_STUDENTS) {
        printf("Maximum students reached!\n");
        return;
    }
    Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter age: ");
    scanf("%d", &s.age);
    printf("Enter GPA: ");
    scanf("%f", &s.gpa);
    students[num_students++] = s;
    saveStudents();
    printf("Student added successfully!\n");
}

void displayStudents() {
    if (num_students == 0) {
        printf("No students found!\n");
        return;
    }
    printf("\nID\tName\t\tAge\tGPA\n");
    printf("--------------------------------\n");
    for (int i = 0; i < num_students; i++) {
        printf("%d\t%s\t\t%d\t%.2f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
}

int findStudent(int id) {
    for (int i = 0; i < num_students; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}

void searchStudent() {
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);
    int idx = findStudent(id);
    if (idx != -1) {
        printf("ID: %d, Name: %s, Age: %d, GPA: %.2f\n", students[idx].id, students[idx].name, students[idx].age, students[idx].gpa);
    } else {
        printf("Student not found!\n");
    }
}

void updateStudent() {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    int idx = findStudent(id);
    if (idx == -1) {
        printf("Student not found!\n");
        return;
    }
    printf("Enter new name: ");
    scanf(" %[^\n]", students[idx].name);
    printf("Enter new age: ");
    scanf("%d", &students[idx].age);
    printf("Enter new GPA: ");
    scanf("%f", &students[idx].gpa);
    saveStudents();
    printf("Student updated successfully!\n");
}

void deleteStudent() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    int idx = findStudent(id);
    if (idx == -1) {
        printf("Student not found!\n");
        return;
    }
    for (int i = idx; i < num_students - 1; i++) {
        students[i] = students[i + 1];
    }
    num_students--;
    saveStudents();
    printf("Student deleted successfully!\n");
}

int main() {
    loadStudents();
    int choice;
    do {
        printf("\n=== Student Management System ===\n");
        printf("1. Add Student\n");
        printf("2. Display All\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
    saveStudents();
    return 0;
}
