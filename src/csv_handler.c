#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_handler.h"
#include "streaming.h"

void RemoveNewLine(char *line) { // function to remove the new line character
    int len = strlen(line);
    if (line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
}

int load_csv(const char *filename, Streaming **stream) {

        FILE *file = fopen(filename, "r"); 
        if (file == NULL) { 
            printf("\033[31mError opening the file %s\033[0m\n", filename);
            return 0;
        }
    
        char line[1024]; // buffer for storing each line of the file
        int count = 0; // conter to store the number of records read
        Streaming *Tempstream = NULL; // pointer to the record
        while (fgets(line, sizeof(line), file)) { 
            RemoveNewLine(line); // remove the new line character
    
            // Reallocation of memory for the new record
            Streaming *new_stream = realloc(Tempstream, (count + 1) * sizeof(Streaming));
            if (new_stream == NULL) { // check if memory was allocated correctly
                printf("\033[31mError allocating memory\033[0m\n");
                free(Tempstream);
                fclose(file);
                return 0;
            }
            Tempstream = new_stream;
    
            // Divide the line into tokens and store them in the record
            char *token = strtok(line, ",");
            if (token != NULL) {
                strncpy(Tempstream[count].title, token, sizeof(Tempstream[count].title) - 1);
                Tempstream[count].title[sizeof(Tempstream[count].title) - 1] = '\0';
            }
    
            token = strtok(NULL, ",");
            if (token != NULL) {
                strncpy(Tempstream[count].genre, token, sizeof(Tempstream[count].genre) - 1);
                Tempstream[count].genre[sizeof(Tempstream[count].genre) - 1] = '\0';
            }
    
            token = strtok(NULL, ",");
            if (token != NULL) {
                Tempstream[count].duration = atoi(token);
            }
    
            token = strtok(NULL, ",");
            if (token != NULL) {
                Tempstream[count].age_rating = atoi(token);
            }
    
            token = strtok(NULL, ",");
            if (token != NULL) {
                Tempstream[count].views = atoi(token);
            }
    
            count++; // increment the number of records read
        }
    
        fclose(file);
        *stream = Tempstream; // update the pointer to the record
        return count; // return the number of records read
}

int save_csv(const char *filename, Streaming *stream, int count) {
    FILE *file = fopen(filename, "w"); // open the file in write mode
    if (file == NULL) { 
        printf("\033[31mError opening the file %s\033[0m\n", filename);
        return 0;
    }

    for (int i = 0; i < count; i++) { // write the records to the file
        fprintf(file, "%s,%s,%d,%d,%d\n", stream[i].title, stream[i].genre, stream[i].duration, stream[i].age_rating, stream[i].views);
    }

    fclose(file); 
    return 1;
}