#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_option.h"
#include "favorite.h"

void AddFavorite(const char *username, const char *title) {
    
    FILE *file = fopen("./data/favorites.csv", "a");

    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    fprintf(file, "%s,%s\n", username, title); // Write to file
    fclose(file);

}
void ShowFavorite(const char *username) {
    
    FILE *file = fopen("./data/favorites.csv", "r");

    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (strcmp(token, username) == 0) {
            printf("%s", strtok(NULL, "\n"));
        }
    }

    fclose(file);

}