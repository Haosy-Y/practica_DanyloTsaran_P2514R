#ifndef MENU_H
#define MENU_H

#include "functions.h"

#define BLUE   "\033[1;34m"
#define GREEN  "\033[1;32m"
#define RED    "\033[1;31m"
#define YELLOW "\033[1;33m"
#define RESET  "\033[0m"

void runMenu(vector<Films>& films, vector<Sessions>& sessions);

#endif