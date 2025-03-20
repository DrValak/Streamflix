#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H
#include "streaming.h"

void RemoveNewLine(char *line);
int load_csv(const char *filename, Streaming **stream);
int save_csv(const char *filename, Streaming *stream, int count);

#endif