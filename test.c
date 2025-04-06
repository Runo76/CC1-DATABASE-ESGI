#include <stdio.h>   
#include <string.h>  
#include <assert.h>  
#include "db.h"  

void test_insert_student() {
    
    FILE* file = fopen("students.csv", "w");
    fclose(file);

    Student student = {1, "Alice", 95.5};
    insert_student(student);

   
    file = fopen("students.csv", "r");
    assert(file != NULL);

    char line[256];
    fgets(line, sizeof(line), file);
    fclose(file);

   
    line[strcspn(line, "\r\n")] = 0; 

    assert(strcmp(line, "1,Alice,95.50") == 0);

    printf("test_insert_student passed.\n");
}