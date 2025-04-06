#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db.h"

#define DATABASE_FILE "students.csv"

void insert_student(Student student) {
    FILE* file = fopen("students.csv", "r");
    if (file == NULL) {
        printf("Error: Could not open database file.\n");
        return;
    }

    fprintf(file, "%d,%s,%.2f\n", student.id, student.name, student.grade);
    fclose(file);

    printf("Student inserted: ID=%d, Name=%s, Grade=%.2f\n", student.id, student.name, student.grade);
}

void select_all_students() {
    FILE* file = fopen("students.csv", "r");
    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    char line[256];
    printf("ID, Name, Grade\n");
    while (fgets(line, sizeof(line), file)) {
        Student student;
        if (sscanf(line, "%d,%49[^,],%f", &student.id, student.name, &student.grade) == 3) {
            printf("%d, %s, %.2f\n", student.id, student.name, student.grade);
        }
    }

    fclose(file);
}

void delete_student(int id) {
    FILE* file = fopen("students.csv", "r");
    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    FILE* temp_file = fopen("temp.csv", "w");
    if (temp_file == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        Student student;
        if (sscanf(line, "%d,%49[^,],%f", &student.id, student.name, &student.grade) == 3) {
            if (student.id != id) {
                fprintf(temp_file, "%d,%s,%.2f\n", student.id, student.name, student.grade);
            } else {
                found = 1;
            }
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        remove(DATABASE_FILE);
        rename("temp.csv", DATABASE_FILE);
        printf("Student with ID %d deleted.\n", id);
    } else {
        remove("temp.csv");
        printf("Student with ID %d not found.\n", id);
    }
}

void select_student_by_id(int id) {
    FILE* file = fopen("students.csv", "r");
    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    char line[256];
    int found = 0;

    printf("ID, Name, Grade\n");
    while (fgets(line, sizeof(line), file)) {
        Student student;
        if (sscanf(line, "%d,%49[^,],%f", &student.id, student.name, &student.grade) == 3) {
            // Check if the student's ID matches the query
            if (student.id == id) {
                printf("%d, %s, %.2f\n", student.id, student.name, student.grade);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No student found with ID %d.\n", id);
    }

    fclose(file);
}