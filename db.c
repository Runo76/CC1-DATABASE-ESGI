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

