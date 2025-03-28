#include <stdio.h>
#include <string.h>
#include "commands.h"

int main() {
    char query[256];

    while (1) {
        printf("db > ");
        fgets(query, sizeof(query), stdin);
        query[strcspn(query, "\n")] = 0; // Remove newline character

        if (strcmp(query, ".exit") == 0) {
            break;
        }

        execute_command(query);
    }

    return 0;
}
