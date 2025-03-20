#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_handler.h"
#include "streaming.h"

void Add(Streaming **stream, int *count) {

    Streaming *new_stream = realloc(*stream, (*count + 1) * sizeof(Streaming)); // realloc memory for the new stream
    if (new_stream == NULL) {
        printf("\033[32mError: Memory allocation failed.\033[0m\n");
        return;
    }

    *stream = new_stream; // update the pointer to the stream

    printf("Enter the Title of Movie/Series: \n");
    fgets((*stream)[*count].title, sizeof((*stream)[*count].title), stdin);
    RemoveNewLine((*stream)[*count].title);

    printf("Enter the Genre of Movie/Serie: \n");
    fgets((*stream)[*count].genre, sizeof((*stream)[*count].genre), stdin);
    RemoveNewLine((*stream)[*count].genre);

    printf("Enter the Duration (minutes): \n");
    scanf("%d", &(*stream)[*count].duration);
    getchar();

    printf("Enter the Age Rating: \n");
    scanf("%d", &(*stream)[*count].age_rating);
    getchar();

    printf("Enter the number of views: \n");
    scanf("%d", &(*stream)[*count].views);
    getchar();

    (*count)++;

    if (save_csv("streaming.csv", *stream, *count)) {
        printf("\033[32mContent added with sucess !\033[0m\n");
    }
    else {
        printf("\033[31mError adding the data\033[0m\n");
    }
}

void Remove(Streaming **stream, int *count) {

    if (*count == 0) { // check if there are any contents to remove
        printf("\033[31mNo contents to remove!\033[0m\n");
        return;
    }

    char title[100]; // buffer to store the title to remove
    printf("Enter the Title of the content to remove: \n");
    fgets(title, sizeof(title), stdin);
    RemoveNewLine(title);

    int index = -1; // index of the content to remove
    for (int i = 0; i < *count; i++) { 
        if (strcmp((*stream)[i].title, title) == 0) {
            index = i;
            break; 
        }
    }

    if (index == -1) { //check if the content was found
        printf("\033[31mContent not found!\033[0m\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) { // loop to move the content to the previous position
        (*stream)[i] = (*stream)[i + 1]; // move the content to the previous position
    }

    Streaming *new_stream = realloc(*stream, (*count - 1) * sizeof(Streaming)); // reallocate memory for the new stream
    if (new_stream == NULL) {
        printf("\033[32mError: Memory allocation failed.\033[0m\n");
        return;
    }

    *stream = new_stream; // update the pointer to the stream
    (*count)--; // decrement the count of contents

    if (save_csv("streaming.csv", *stream, *count)) { // check if the content was removed
        printf("\033[32mContent erased with sucess! \033[0m\n");
    }
    else {
        printf("\033[32mError removing the content\033[0m\n");
    }
}

void Edit(Streaming **stream, int *count) {

    if (*count == 0) {
        printf("\033[31mThere are no contents to edit\033[0m\n");
        return;
    }

    char title[100];
    printf("Enter the Title of the Movie/Series to edit: \n");
    fgets(title, sizeof(title), stdin);
    RemoveNewLine(title);

    int index = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp((*stream)[i].title, title) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("\033[31mContent not found!\033[0m\n");
        return;
    }

    printf("Enter new Title: \n");
    fgets((*stream)[index].title, sizeof((*stream)[index].title), stdin);
    RemoveNewLine((*stream)[index].title);

    printf("Enter new Genre: \n");
    fgets((*stream)[index].genre, sizeof((*stream)[index].genre), stdin);
    RemoveNewLine((*stream)[index].genre);

    printf("Enter new Duration (minutes): \n");
    scanf("%d", &(*stream)[index].duration);
    getchar();

    printf("Enter new age rating: \n");
    scanf("%d", &(*stream)[index].age_rating);
    getchar();

    printf("Enter new value for views: \n");
    scanf("%d", &(*stream)[index].views);
    getchar();

    if (save_csv("streaming.csv", *stream, *count)) {
        printf("\033[32mContent edited with sucess! \033[0m\n");
    }
    else {
        printf("\033[31mError editing the content\033[0m\n");
    }

}

void Search(Streaming *stream, int count) {

    if (count == 0) {
        printf("\033[31mNo contents to search\033[0m\n");
        return;
    }

    int option;
    printf("Choose a field for search please: \n");
    printf("1 - Títle\n");
    printf("2 - Genre\n");
    printf("3 - Age Rating\n");
    scanf("%d", &option);
    getchar();

    if (option < 1 || option > 3) {
        printf("\033[31mInvalid Option, please select 1,2 or 3\033[0m\n");
        return;
    }

    if (option == 1) {
        char SearchTitle[100];
        printf("Enter the Title to search: \n");
        fgets(SearchTitle, sizeof(SearchTitle), stdin);
        RemoveNewLine(SearchTitle);

        printf("\033[34mResults of the search:\033[0m\n");
        for (int i = 0; i < count; i++) {
            if (strstr((stream)[i].title, SearchTitle) != NULL) {
                printf("Title: %s\n", (stream)[i].title);
                printf("Genre: %s\n", (stream)[i].genre);
                printf("Duration: %d minutos\n", (stream)[i].duration);
                printf("Age Rating: %d\n", (stream)[i].age_rating);
                printf("Views: %d\n", (stream)[i].views);
                printf("\n");
            }
        }
    }
    else if (option == 2) {
        char SearchGenre[100];
        printf("Enter the Genre to search: \n");
        fgets(SearchGenre, sizeof(SearchGenre), stdin);
        RemoveNewLine(SearchGenre);

        printf("\033[34mResultados da pesquisa:\033[0m\n");
        for (int i = 0; i < count; i++) {
            if (strstr((stream)[i].genre, SearchGenre) != NULL) {
                printf("Title: %s\n", (stream)[i].title);
                printf("Genre: %s\n", (stream)[i].genre);
                printf("Duration: %d minutos\n", (stream)[i].duration);
                printf("Age Rating: %d\n", (stream)[i].age_rating);
                printf("Views: %d\n", (stream)[i].views);
                printf("\n");
            }
        }
    }
    else if (option == 3) {
        int Search_age_rating;
        printf("Enter the age rating: \n");
        scanf("%d", &Search_age_rating);
        getchar();

        printf("\033[34mResultados da pesquisa:\033[0m\n");
        for (int i = 0; i < count; i++) {
            if ((stream)[i].age_rating == Search_age_rating) {
                printf("Títle: %s\n", (stream)[i].title);
                printf("Genre: %s\n", (stream)[i].genre);
                printf("Duration: %d minutos\n", (stream)[i].duration);
                printf("Age Rating: %d\n", (stream)[i].age_rating);
                printf("Views: %d\n", (stream)[i].views);
                printf("\n");
            }
        }
    }
    else {
        printf("\033[31mInvalid option\033[0m\n");
    }
}