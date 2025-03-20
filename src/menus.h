#ifndef MENUS_H
#define MENUS_H
#include "streaming.h"
#include "favorite.h"
#include "personal_list.h"

void showMainMenu();
void showFavoritesMenu(List **lists, int *listCount, int catalogCount);
void manageCatalog(Streaming **catalog, int *catalogCount);
void showrecommendationsMenu(Streaming *catalog, int catalogCount);
void actionsMenu(Streaming *catalog, int catalogCount, const char *interactionFile);
void showListsMenu(List **lists, int *listCount);
void showReportsMenu(Streaming *catalog, int catalogCount);

#endif