#ifndef DATABASE_H
#define DATABASE_H

typedef struct {
    int id;
    char name[50];
    float grade;
} Student;

void insert_student(Student student);
void select_all_students();
void select_student_by_id(int id);  // Add this declaration
void delete_student(int id);


#endif
