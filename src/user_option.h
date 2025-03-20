#ifndef USER_OPTION_H
#define USER_OPTION_H
#include "streaming.h"

typedef struct {
    char username[100];
    char title[100];
    char action[10]; // play, pause, resume
} User;

void User_action(const char *filename, const char *title, const char *username, const char *action);
void User_option(const char *filename, User **interactions, int *count);
void Show_option(const char *filename, const char *title, const char *username);

#endif