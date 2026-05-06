#include <bits/stdc++.h>
using namespace std;
struct Films {
    int id;
    string name, genre;
    string duration;
    string agelimit;
};
struct Sessions {
    int sid;
    int filmId;
    string date;
    string time;
    int hallId;
    int price;
};


int main() {
    ifstream file1("movie.txt");
    ifstream file2("session.txt");
    if (!file1.is_open() || !file2.is_open()) {
        cout << "Ошибка: не удалось открыть movie.txt или session.txt\n";
        return 1;
    }

    vector<Films> films;
    vector<Sessions> sessions;

    Films film;
    while (file1 >> film.id >> film.name >> film.genre >> film.duration >> film.agelimit) {
        films.push_back(film);
    }

    Sessions session;
    while (file2 >> session.sid >> session.filmId >> session.date >> session.time >> session.hallId >> session.price) {
        sessions.push_back(session);
    }


    return 0;
} 