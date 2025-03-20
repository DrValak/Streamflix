#ifndef STREAMING_H
#define STREAMING_H

typedef struct {
    char title[100]; // Title of the movie or series
    char genre[100]; // Genre of the movie or series
    int duration; // Duration of the movie or series
    int age_rating; // Age rating of the movie or series
    int views;  // Number of views of the movie or series
} Streaming;

void Add(Streaming **stream, int *count);
void Remove(Streaming **stream, int *count);
void Edit(Streaming **stream, int *count);
void Search(Streaming *stream, int count);

#endif