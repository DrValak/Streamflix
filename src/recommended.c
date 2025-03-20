#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "streaming.h"

void recommended(const char *username, Streaming *catalog, int catalogCount) {

    FILE *file = fopen("./data/interactions.csv","r");
    if (file == NULL) {
        printf("\033[31mError opening file!\033[0m\n"); //Error opening the file (red color)
        exit(1);
    }

    char favoriteGenres[8][25]; // 8 genres, 25 characters each
    int favoriteGenresCount = 0; // number of favorite genres
    char watchedTitles[25][100]; // 25 titles, 100 characters each
    int watchedTitlesCount = 0; // number of watched titles

    char line[1024];
    while (fgets(line, 1024, file)) {
        char *file_username = strtok(line, ",");
        char *title = strtok(NULL, ",");
        char *action = strtok(NULL, ",");

        if (strcmp(file_username,username) == 0 && strcmp(action,"play") == 0) {
            // add title to watchedTitles
            strcpy(watchedTitles[watchedTitlesCount], title);
            watchedTitlesCount++;

            for (int i = 0; i < catalogCount; i++) {
                if (strcmp(catalog[i].title,title) == 0) {
                    int found = 0;
                    for (int j = 0; j < favoriteGenresCount; j++) {
                        if (strcmp(catalog[i].genre,favoriteGenres[j]) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found && favoriteGenresCount < 8) {
                        strcpy(favoriteGenres[favoriteGenresCount], catalog[i].genre);
                        favoriteGenresCount++;
                    }
                    break;
                }
            
            }
        }
    }
    fclose(file);

    printf("\033[32mRecommended for %s:\033[0m\n", username);
    int recommendations = 0;
    for (int i = 0; i < catalogCount; i++) {
        // check if the title is already watched
        int alreadyWatched = 0;
        for (int j = 0; j < watchedTitlesCount; j++) {
            if (strcmp(catalog[i].title, watchedTitles[j]) == 0) {
                alreadyWatched = 1;
                break;
            }
        }

        // check if the genre is a favorite genre
        int isFavoriteGenre = 0;
        for (int j = 0; j < favoriteGenresCount; j++) {
            if (strcmp(catalog[i].genre, favoriteGenres[j]) == 0) {
                isFavoriteGenre = 1;
                break;
            }
        }

        // Recommend the title if it was not watched and is from a favorite genre
        if (!alreadyWatched && isFavoriteGenre) {
            printf("- %s (%s) - %d views\n", catalog[i].title, catalog[i].genre, catalog[i].views);
            recommendations++;
        }
    }

    if (recommendations == 0) {
        printf("\033[31mNo recommendations available.\033[0m\n");
    }
}