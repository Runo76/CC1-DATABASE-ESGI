#include "table.h"
#include <stdio.h>

void print_line(Line* line) {
    printf("(%d, %s, %s)\n", line->id, line->username, line->email);
}
