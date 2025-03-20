#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "report.h"
#include "streaming.h"

void mostWatchedContent() {
    FILE *file = fopen("./data/interactions.csv", "r");

    if (file == NULL) {
        printf("\033[31mError: File not found\033[0m\n");
        return;
    }

    Streaming contents[1000]; // Array to store all the contents
    int contentCount = 0; // Number of contents

    char line[1024]; // Buffer to store each line of the file
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character

        strtok(line, ","); // Skip the username
        char *title = strtok(NULL, ",");   // Get the title
        char *action = strtok(NULL, ","); // Get the action

        if (strcmp(action, "play") == 0) { // If the action is play
            int found = 0;
            for (int i = 0; i < contentCount; i++) { // Check if the content is already in the array
                if (strcmp(contents[i].title, title) == 0) {
                    contents[i].views++;
                    found = 1;
                    break;
                }
            }
            if (!found) { // If the content is not in the array
                strcpy(contents[contentCount].title, title);
                contents[contentCount].views = 1;
                contentCount++;
            }
        }
    }
    fclose(file);

    // Sort the contents by views
    for (int i = 0; i < contentCount; i++) {
        for (int j = i + 1; j < contentCount; j++) {
            if (contents[i].views < contents[j].views) {
                Streaming temp = contents[i];
                contents[i] = contents[j];
                contents[j] = temp;
            }
        }
    }

    printf("\033[32mMost watched content:\033[0m\n");
    for (int i = 0; i < contentCount; i++) {
        printf("%s: %d views\n", contents[i].title, contents[i].views);
    }
}

void topActiveUsers() {
    FILE *file = fopen("./data/interactions.csv", "r");

    if (file == NULL) {
        printf("\033[31mError: File not found\033[0m\n");
        return;
    }

    typedef struct {
        char username[256];
        int actions;
    } ReportUser;

    ReportUser users[1000]; // Array to store all the users
    int usersCount = 0; // Number of users

    char line[1024]; // Buffer to store each line of the file
    while (fgets(line, sizeof(line), file)) {
        char *username = strtok(line, ",");
        strtok(NULL, ","); // Skip the title
        strtok(NULL, ","); // Skip the action

        int found = 0;
        for (int i = 0; i < usersCount; i++) {
            if (strcmp(users[i].username, username) == 0) {
                users[i].actions++;
                found = 1;
                break;
            }
        }
        if (!found) { // If the user is not in the array
            strcpy(users[usersCount].username, username);
            users[usersCount].actions = 1;
            usersCount++;
        }
    }
    fclose(file);

    // Sort the users by number of actions
    for (int i = 0; i < usersCount; i++) {
        for (int j = i + 1; j < usersCount; j++) {
            if (users[i].actions < users[j].actions) {
                ReportUser temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    // Display most active users
    printf("\033[32mMost active users:\033[0m\n");
    for (int i = 0; i < usersCount; i++) {
        printf("%s: %d actions\n", users[i].username, users[i].actions);
    }
}

void mostWatchedGenre(Streaming *catalog, int catalogCount) {
    if (catalogCount == 0) {
        printf("\033[31mError: Catalog is empty.\033[0m\n");
        return;
    }

    FILE *file = fopen("./data/interactions.csv", "r");
    if (file == NULL) {
        printf("\033[31mError: File not found.\033[0m\n");
        return;
    }

    typedef struct {
        char genre[256];
        int views;
    } GenreReport;

    GenreReport genres[100]; // Array to store genres and their view counts
    int genreCount = 0; // Number of genres

    char line[1024]; // Buffer to store each line of the file
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character

        strtok(line, ","); // Skip the username
        char *title = strtok(NULL, ",");   // Get the title
        char *action = strtok(NULL, ","); // Get the action

        if (title == NULL || action == NULL) {
            printf("Debug: Skipping malformed line.\n");
            continue;
        }

        if (strcmp(action, "play") == 0) { // If the action is play
            // Find the genre of the title in the catalog
            for (int i = 0; i < catalogCount; i++) {
                if (strcmp(catalog[i].title, title) == 0) {
                    char *genre = catalog[i].genre;

                    // Check if the genre is already in the array
                    int found = 0;
                    for (int j = 0; j < genreCount; j++) {
                        if (strcmp(genres[j].genre, genre) == 0) {
                            genres[j].views++;
                            found = 1;
                            break;
                        }
                    }
                    if (!found) { // If the genre is not in the array
                        strcpy(genres[genreCount].genre, genre);
                        genres[genreCount].views = 1;
                        genreCount++;
                    }
                    break;
                }
            }
        }
    }
    fclose(file);

    // Sort the genres by views
    for (int i = 0; i < genreCount; i++) {
        for (int j = i + 1; j < genreCount; j++) {
            if (genres[i].views < genres[j].views) {
                GenreReport temp = genres[i];
                genres[i] = genres[j];
                genres[j] = temp;
            }
        }
    }

    printf("\033[32mMost watched genres:\033[0m\n");
    for (int i = 0; i < genreCount; i++) {
        printf("%s: %d views\n", genres[i].genre, genres[i].views);
    }
}