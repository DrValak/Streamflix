#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personal_list.h"
#include "streaming.h"
#include "csv_handler.h"

void saveListsToCSV(List *lists, int listCount) {

    char filename[] = "./data/lists.csv"; // Name of the file

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("\033[31mError: Could not open file '%s' for writing.\033[0m\n", filename);
        return;
    }

    for (int i = 0; i < listCount; i++) {
        fprintf(file, "%s", lists[i].listName); // Write the list name

        for (int j = 0; j < lists[i].titleCount; j++) {
            fprintf(file, ",%s", lists[i].titles[j]); // Write the titles

        fprintf(file, "\n"); // Nova linha para a próxima lista
    }

    fclose(file);
    printf("\033[32mLists saved successfully to '%s'.\033[0m\n", filename);
    }
}

void loadListsFromCSV(const char *filename, List **lists, int *listCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\033[31mError: Could not open file '%s' for reading.\033[0m\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove the newline character

        List *newLists = realloc(*lists, sizeof(List) * (*listCount + 1));
        if (newLists == NULL) {
            printf("\033[31mError: Memory allocation failed.\033[0m\n");
            fclose(file);
            return;
        }

        *lists = newLists;
        List *currentList = &(*lists)[*listCount];
        currentList->titles = NULL;
        currentList->titleCount = 0;

        char *token = strtok(line, ",");
        strncpy(currentList->listName, token, sizeof(currentList->listName) - 1);
        currentList->listName[sizeof(currentList->listName) - 1] = '\0'; // Ensure null termination

        while ((token = strtok(NULL, ",")) != NULL) {
            char **newTitles = realloc(currentList->titles, sizeof(char *) * (currentList->titleCount + 1));
            if (newTitles == NULL) {
                printf("\033[31mError: Memory allocation failed.\033[0m\n");
                fclose(file);
                return;
            }

            currentList->titles = newTitles;
            currentList->titles[currentList->titleCount] = malloc((strlen(token) + 1) * sizeof(char));
            if (currentList->titles[currentList->titleCount] == NULL) {
                printf("\033[31mError: Memory allocation failed.\033[0m\n");
                fclose(file);
                return;
            }
            strcpy(currentList->titles[currentList->titleCount], token);
            currentList->titleCount++;
        }

        (*listCount)++;
    }

    fclose(file);
    printf("\033[32mLists loaded successfully from '%s'.\033[0m\n", filename);
}

void createList(List **lists, int *listCount) {
    List *newLists = realloc(*lists, sizeof(List) * (*listCount + 1));
    if (newLists == NULL) {
        return;
    }

    *lists = newLists; // Update the pointer to the new memory

    printf("Enter the name of the list: ");
    fgets((*lists)[*listCount].listName, sizeof((*lists)[*listCount].listName), stdin);
    RemoveNewLine((*lists)[*listCount].listName);

    (*lists)[*listCount].titles = NULL; // Initialize the titles array to NULL
    (*lists)[*listCount].titleCount = 0; // Initialize the title count to 0
    (*listCount)++;

    printf("\033[32mList '%s' created with sucess!\033[0m\n", (*lists)[*listCount - 1].listName);

    saveListsToCSV(*lists, *listCount); // Save the lists to the CSV file
}

void addToList(List *list, int listCount) {

    if (listCount == 0) {
        printf("\033[31mNo list was found\033[0m\n");
        return;
    }

    printf("Choose a list for adding content\n");
    for (int i = 0; i < listCount; i++) {
        printf("%d - %s\n", i + 1, list[i].listName);
    }

    int choice; // Variable to store the user choice
    scanf("%d", &choice);
    getchar(); // Clear the buffer

    if (choice < 1 || choice > listCount) { // Check if the choice is valid
        printf("\033[31mInvalid choice\033[0m\n");
        return;
    }

    List *selectedList = &list[choice - 1];

    printf("Enter the title of the content: ");
    char title[100]; // Variable to store the title
    fgets(title, sizeof(title), stdin); // Read the title from the user
    title[strcspn(title, "\n")] = 0; // Remove the newline character

    char *newTitle = malloc((strlen(title) + 1) * sizeof(char)); // Allocate memory for the new title
    if (newTitle == NULL) {
        printf("\033[32mError: Memory allocation failed.\033[0m\n");
        return;
    }

    strcpy(newTitle, title); // Copy the title to the new memory

    char **newTitles = realloc(selectedList->titles, sizeof(char *));
    if (newTitles == NULL) {
        printf("\033[32mError: Memory allocation failed.\033[0m\n");
        return;
    }
    
    selectedList->titles = newTitles; // Update the pointer to the new memory
    selectedList->titles[selectedList->titleCount] = newTitle; // Update the pointer to the new titles
    selectedList->titleCount++;

    printf("\033[32mContent '%s' added to the list '%s' with success!\033[0m\n", title, selectedList->listName);

    saveListsToCSV(list, listCount); // Save the lists to the CSV file
}

void showList(List *list, int listCount) {
    if (listCount == 0) {
        printf("\033[31mNo list was found.\033[0m\n");
        return;
    }

    printf("Choose a list to show:\n");
    for (int i = 0; i < listCount; i++) {
        printf("%d - %s\n", i + 1, list[i].listName);
    }

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Clear the buffer

    if (choice < 1 || choice > listCount) {
        printf("\033[31mInvalid choice.\033[0m\n");
        return;
    }

    List selectedList = list[choice - 1];
    printf("\033[32mList '%s' content:\033[0m\n", selectedList.listName);
    for (int i = 0; i < selectedList.titleCount; i++) {
        printf("%d - %s\n", i + 1, selectedList.titles[i]);
    }
}

void removeFromList(List *list, int listCount) {
    if (listCount == 0) { // Check if there are lists
        printf("\033[31mNo list was found\033[0m\n");
        return;
    }

    printf("Choose a list to remove content\n");
    for (int i = 0; i < listCount; i++) { // Show the list names
        printf("%d - %s\n", i + 1, list[i].listName);
    }

    int choice; // Variable to store the user choice
    scanf("%d", &choice);
    getchar(); // Clear the buffer

    if (choice < 1 || choice > listCount) { // Check if the choice is valid
        printf("\033[31mInvalid choice\033[0m\n");
        return;
    }

    List *selectedList = &list[choice - 1]; // Get the selected list

    if (selectedList->titleCount == 0) {
        printf("\033[31mNo content was found in the list\033[0m\n");
        return;
    }

    printf("Choose a content to remove\n"); // Show the titles of the selected list
    for (int i = 0; i < selectedList->titleCount; i++) {
        printf("%d - %s\n", i + 1, selectedList->titles[i]);
    }

    int contentChoice; // Variable to store the user choice
    scanf("%d", &contentChoice);
    getchar(); // Clear the buffer

    if (contentChoice < 1 || contentChoice > selectedList->titleCount) {
        printf("\033[31mInvalid choice\033[0m\n");
        return;
    }

    free(selectedList->titles[contentChoice - 1]); // Free the memory allocated for the title
    selectedList->titleCount--;

    for (int i = contentChoice - 1; i < selectedList->titleCount; i++) {
        selectedList->titles[i] = selectedList->titles[i + 1]; // Move the pointers to the left
    }

    char **newTitles = realloc(selectedList->titles, sizeof(char *) * selectedList->titleCount);
    if (newTitles == NULL) {
        printf("\033[31mError: Memory allocation failed.\033[0m\n");
        return;
    }

    selectedList->titles = newTitles; // Update the pointer to the new memory

    printf("\033[32mContent removed with success!\033[0m\n");

    saveListsToCSV(list, listCount); // Save the lists to the CSV file
}

void freeLists(List *list, int listCount) {
    for (int i = 0; i < listCount; i++) {
        for (int j = 0; j < list[i].titleCount; j++) {
            free(list[i].titles[j]); // Free the memory allocated for the titles
        }
        free(list[i].titles); // Free the memory allocated for the titles array
    }
    free(list); // Free the memory allocated for the lists
}