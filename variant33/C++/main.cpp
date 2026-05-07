#include <bits/stdc++.h>
#include "functions.h"
using namespace std;

int main() {
    vector<Films> films = loadFilms();
    vector<Sessions> sessions = loadSessions();

    runMenu(films, sessions);

    return 0;
}