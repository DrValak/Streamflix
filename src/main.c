#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv_handler.h"
#include "streaming.h"
#include "menus.h"
#include "favorite.h"
#include "recommended.h"
#include "report.h"
#include "personal_list.h"
#include "user_option.h"


int main() {
    Streaming *new_streaming = NULL;
    List *lists = NULL;
    int catalogCount = 0, listCount = 0;
    int option;

    // Load the streaming catalog
    catalogCount = load_csv("data/catálogo.csv", &new_streaming);
    // Load the lists
    loadListsFromCSV("data/lists.csv", &lists, &listCount);


    printf("\033[32m%d contents loaded from the catalog.\033[0m\n", catalogCount); // Message with sucess in green color

    do {
        showMainMenu();
        scanf("%d", &option);
        getchar(); // Clean buffer

        switch (option) {
            case 1:
                // Streaming Catalog
                manageCatalog(&new_streaming, &catalogCount);
                break;
            case 2:
                // Submenu Favorites
                showFavoritesMenu(&lists, &listCount, catalogCount);
                break;
            case 3:
                // Submenu Recommendations
                showrecommendationsMenu(new_streaming, catalogCount);
                break;
            case 4:
                // Submenu Actions
                actionsMenu(new_streaming, catalogCount, "data/interactions.csv");
                break;
            case 5:
                // Submenu Lists
                showListsMenu(&lists, &listCount);
                break;
            case 6:
                // Submenu Reports
                showReportsMenu(new_streaming, catalogCount);
                break;
            case 7:
                printf("\033[33mGoing out of the program...\033[0m\n"); // Yellow
                break;
            default:
                printf("\033[31mOption not valid. Try again please.\033[0m\n"); // Red
        }

    } while (option != 7);

    // Free memory
    free(new_streaming);
    freeLists(lists, listCount);

    return 0;
}