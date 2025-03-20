#ifndef PERSONAL_LIST_H
#define PERSONAL_LIST_H
#include "streaming.h"
#include "csv_handler.h"

typedef struct {
    char listName[50]; // Name of the list
    char **titles; // Array of titles
    int titleCount; // Number of titles
} List;

void saveListToCSV(const char *filename, List *list, int listCount);
void loadListsFromCSV(const char *filename, List **lists, int *listCount);
void createList(List **list, int *listCount);
void addToList(List *list, int listCount);
void showList(List *list, int listCount);
void removeFromList(List *list, int listCount);
void freeLists(List *list, int listCount);

#endif