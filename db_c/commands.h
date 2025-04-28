#ifndef COMMANDS_H
#define COMMANDS_H

#include "btree.h"

// Function declarations
void insert_student(Student student);
void select_all_students();
void select_student_by_id(int id);
void delete_student(int id);

void execute_command(const char* query);

#endif
