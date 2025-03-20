#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#include "streaming.h"
#include "favorite.h"
#include "personal_list.h"
#include "recommended.h"
#include "report.h"

void showMainMenu() {
    printf("\033[1;34m===== MENU STREAMFLIX =====\033[0m\n"); // Title in blue and bold
    printf("\033[33m1 - Streaming Catalog\033[0m\n"); // yellow
    printf("\033[33m2 - Favorites\033[0m\n"); 
    printf("\033[33m3 - Recommendations\033[0m\n"); 
    printf("\033[33m4 - Actions\033[0m\n");
    printf("\033[33m5 - Lists\033[0m\n");
    printf("\033[33m6 - Reports\033[0m\n"); 
    printf("\033[33m7 - Leave\033[0m\n"); 
    printf("\033[1;34m===========================\033[0m\n"); // blue and bold
    printf("Choose an option please:\n ");
}

void manageCatalog(Streaming **catalog, int *catalogCount) {
    int option;
    do {
        printf("\n\033[1;34m===== CATALOG MENU =====\033[0m\n"); // Title in blue and bold
        printf("\033[33m1 - Add Content\033[0m\n"); // Yellow
        printf("\033[33m2 - Remove Content\033[0m\n");
        printf("\033[33m3 - Edit Content\033[0m\n");
        printf("\033[33m4 - Search Content\033[0m\n");
        printf("\033[33m5 - Back to Main Menu\033[0m\n");
        printf("\033[1;34m===========================\033[0m\n"); // Blue and bold
        printf("Choose an option: ");
        scanf("%d", &option);
        getchar(); // Clean buffer

        switch (option) {
            case 1:
                Add(catalog, catalogCount);
                break;
            case 2:
                Remove(catalog, catalogCount);
                break;
            case 3:
                Edit(catalog, catalogCount);
                break;
            case 4:
                Search(*catalog, *catalogCount);
                break;
            case 5:
                printf("Backing to Main Menu...\n");
                break;
            default:
                printf("Option not valid!\n");
        }
    } while (option != 5);
}

void showFavoritesMenu(List **lists, int *listCount, int catalogCount) {
    int option;

    do {
        printf("\n\033[1;34m===== FAVORITES MENU =====\033[0m\n"); // Title in blue and bold
        printf("\033[33m1 - Add to Favorites\033[0m\n"); // Yellow
        printf("\033[33m2 - Show Favorites\033[0m\n");
        printf("\033[33m3 - Back to Main Menu\033[0m\n");
        printf("\033[1;34m===========================\033[0m\n"); // Blue and bold
        printf("Choose an option: ");
        scanf("%d", &option);
        getchar(); // Clean the buffer

        switch (option) {
            case 1:
                // Adding content to favorites
                if (catalogCount == 0) {
                    printf("No content available in the catalog.\n");
                } else {
                    addToList(*lists, *listCount);
                }
                break;
            case 2:
                // Showing favorites
                if (*listCount == 0) {
                    printf("No favorite lists available.\n");
                } else {
                    showList(*lists, *listCount);
                }
                break;
            case 3:
                printf("Returning to the main menu...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 3);
}

void showrecommendationsMenu(Streaming *catalog, int catalogCount) {
    char username[50];

    printf("\n\033[1;34m===== RECOMMENDATIONS MENU =====\033[0m\n"); // Title in blue and bold
    printf("Enter the username to check recommendations: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    recommended(username, catalog, catalogCount);

    printf("\033[33mPress Enter to return to the Main Menu...\033[0m\n"); // Yellow
    getchar();
}

void actionsMenu(Streaming *catalog, int catalogCount, const char *interactionFile) {
    if (catalogCount == 0) {
        printf("\033[31mNo content available in the catalog.\033[0m\n"); // Red for errors
        return;
    }

    int contentChoice, actionChoice;
    char *actions[] = {"play", "pause", "resume"};

    printf("\n\033[1;34m===== ACTIONS MENU =====\033[0m\n"); // Title in blue and bold
    printf("\033[33mChoose a content to perform an action:\033[0m\n"); // Yellow
    for (int i = 0; i < catalogCount; i++) {
        printf("\033[33m%d - %s\033[0m\n", i + 1, catalog[i].title); // Yellow
    }
    printf("\033[1;34m===========================\033[0m\n"); // Blue and bold
    printf("Enter the number of the content: ");
    scanf("%d", &contentChoice);
    getchar(); // Clean buffer

    if (contentChoice < 1 || contentChoice > catalogCount) {
        printf("\033[31mInvalid content choice. Returning to Main Menu.\033[0m\n"); // Red for errors
        return;
    }

    printf("\033[33mChoose an action to perform:\033[0m\n"); // Yellow
    printf("\033[33m1 - Play\033[0m\n");
    printf("\033[33m2 - Pause\033[0m\n");
    printf("\033[33m3 - Resume\033[0m\n");
    printf("\033[1;34m===========================\033[0m\n"); // Blue and bold
    printf("Enter the number of the action: ");
    scanf("%d", &actionChoice);
    getchar(); // Clean buffer

    if (actionChoice < 1 || actionChoice > 3) {
        printf("\033[31mInvalid action choice. Returning to Main Menu.\033[0m\n"); // Red for errors
        return;
    }

    FILE *file = fopen(interactionFile, "a");
    if (file == NULL) {
        printf("\033[31mError: Unable to open the interactions file.\033[0m\n"); // Red for errors
        return;
    }

    fprintf(file, "%s,%s,%s\n", "user1", catalog[contentChoice - 1].title, actions[actionChoice - 1]);
    fclose(file);

    printf("\033[32mAction '%s' performed on content '%s'.\033[0m\n", actions[actionChoice - 1], catalog[contentChoice - 1].title); // Green for success
}

void showListsMenu(List **lists, int *listCount) {
    int option;

    do {
        printf("\n\033[1;34m===== LISTS MENU =====\033[0m\n"); // Title in blue and bold
        printf("\033[33m1 - Create a New List\033[0m\n"); // Yellow
        printf("\033[33m2 - Add Content to a List\033[0m\n");
        printf("\033[33m3 - Show a List\033[0m\n");
        printf("\033[33m4 - Remove Content from a List\033[0m\n");
        printf("\033[33m5 - Back to Main Menu\033[0m\n");
        printf("\033[1;34m===========================\033[0m\n"); // Blue and bold
        printf("Choose an option: ");
        scanf("%d", &option);
        getchar(); // Clean buffer

        switch (option) {
            case 1:
                // Making a new list
                createList(lists, listCount);
                break;
            case 2:
                // Adding content to the list
                addToList(*lists, *listCount);
                break;
            case 3:
                // Show list
                showList(*lists, *listCount);
                break;
            case 4:
                // Removing content from the list
                removeFromList(*lists, *listCount);
                break;
            case 5:
                printf("\033[33mReturning to Main Menu...\033[0m\n\n"); // Yellow
                break;
            default:
                printf("\033[31mInvalid option! Please try again.\033[0m\n\n"); // Red for errors
        }
    } while (option != 5);
}

void showReportsMenu(Streaming *catalog, int catalogCount) {
    int option;

    do {
        printf("\n\033[1;34m===== REPORTS MENU =====\033[0m\n"); // Title in blue and bold
        printf("\033[33m1 - Most Watched Content\033[0m\n"); // Yellow
        printf("\033[33m2 - Most Active Users\033[0m\n");
        printf("\033[33m3 - Most Watched Genres\033[0m\n");
        printf("\033[33m4 - Back to Main Menu\033[0m\n");
        printf("\033[1;34m===========================\033[0m\n"); // Blue and bold
        printf("Choose an option: ");
        scanf("%d", &option);
        getchar(); // Clean buffer

        switch (option) {
            case 1:
                mostWatchedContent();
                break;
            case 2:
                topActiveUsers();
                break;
            case 3:
                mostWatchedGenre(catalog, catalogCount);
                break;
            case 4:
                printf("\033[33mReturning to Main Menu...\033[0m\n\n"); // Yellow
                break;
            default:
                printf("\033[31mInvalid option! Please try again.\033[0m\n\n"); // Red for errors
        }
    } while (option != 4);
}