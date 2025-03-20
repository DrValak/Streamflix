#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_option.h"

filename = "./data/interactions.csv";

void User_action(const char *filename, const char *title, const char *username, const char *action) {

    char action[10]; // play, pause, resume

    printf("\033[32mChoose an action: \033[0m\n");
    scanf("%s", action);
    getchar(); // Capture '\n' from scanf

    if (strcmp(action, "play") != 0 && strcmp(action, "pause") != 0 && strcmp(action, "resume") != 0) { // Check if action is valid
        printf("\033[31mInvalid action! Try again.\033[0m\n");
        return 1;
    }

    FILE *file = fopen(filename, "a"); // Open file in append mode
    
    if (file == NULL) {
        printf("\033[31mError: Could not open file\033[0m\n");
        return 1;
    }

    fprintf(file, "%s %s %s\n", title, username, action); // Write to file , the title, username and action
    fclose(file);
}

void User_option(const char *filename, User **interactions, int *count) {

    FILE *file = fopen(filename, "r"); // Open file in read mode

    if (file == NULL) {
        printf("\033[31mError: Could not open file\033[0m\n");
        return 1;
    }

    char line[256]; // Buffer to store each line of the file
    *count = 0; // Initialize count to 0

    while (fgets(line, sizeof(line), file)) {
        User *new_interaction = realloc(*interactions, (*count + 1) * sizeof(User)); // Allocate memory for new interaction

        if (new_interaction == NULL) {
            printf("\033[31mError: Could not allocate memory\033[0m\n");
            return 1;
        }

        *interactions = new_interaction; // Update interactions
        sscanf(line, "%s %s %s", (*interactions)[*count].title, (*interactions)[*count].username, (*interactions)[*count].action); // Parse line
        (*count)++; // Increment count

        fclose(file);
    }
}

void Show_option(const char *filename, User *interactions, int count) {

    printf("\033[32mPlease enter your username: \033[0m\n");
    char username[100];
    scanf("%s", username);
    getchar(); // Capture '\n' from scanf

    for (int i = 0; i < count; i++) {
        if (strcmp(interactions[i].username, username) == 0) {
            printf("Title: %s\n", interactions[i].title);
            printf("Action: %s\n", interactions[i].action);
        }
        else {
            printf("\033[31mNo interactions found for this username\033[0m\n");
        }
    }

    return 0;

}