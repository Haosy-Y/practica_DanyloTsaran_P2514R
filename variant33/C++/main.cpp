#include <bits/stdc++.h>
#include "menu.h"

using namespace std;

int main() {
    vector<Films> films = loadFilms();
    vector<Sessions> sessions = loadSessions();

    runMenu(films, sessions);

    return 0;
}