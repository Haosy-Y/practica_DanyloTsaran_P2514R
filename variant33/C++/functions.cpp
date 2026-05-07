#include "functions.h"

// load
vector<Films> loadFilms() {
    vector<Films> films;
    ifstream file("x-movie.txt");

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Films f;
        string tmp;

        getline(ss, tmp, '|'); f.id = stoi(tmp);
        getline(ss, f.name, '|');
        getline(ss, f.genre, '|');
        getline(ss, f.duration, '|');
        getline(ss, f.agelimit, '|');

        films.push_back(f);
    }

    return films;
}

vector<Sessions> loadSessions() {
    vector<Sessions> sessions;
    ifstream file("x-session.txt");

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Sessions s;
        string tmp;

        getline(ss, tmp, '|'); s.sid = stoi(tmp);
        getline(ss, tmp, '|'); s.filmId = stoi(tmp);
        getline(ss, s.date, '|');
        getline(ss, s.time, '|');
        getline(ss, tmp, '|'); s.hallId = stoi(tmp);
        getline(ss, tmp, '|'); s.price = stoi(tmp);

        sessions.push_back(s);
    }

    return sessions;
}

// save
void saveFilms(const vector<Films>& films) {
    ofstream file("x-movie.txt", ios::trunc);

    for (const auto& f : films) {
        file << f.id << "|"
             << f.name << "|"
             << f.genre << "|"
             << f.duration << "|"
             << f.agelimit << "\n";
    }
}

void saveSessions(const vector<Sessions>& sessions) {
    ofstream file("x-session.txt", ios::trunc);

    for (const auto& s : sessions) {
        file << s.sid << "|"
             << s.filmId << "|"
             << s.date << "|"
             << s.time << "|"
             << s.hallId << "|"
             << s.price << "\n";
    }
}

// print
void printFilms(const vector<Films>& films) {
    for (auto& f : films) {
        cout << f.id << " "
             << f.name << " "
             << f.genre << " "
             << f.duration << " "
             << f.agelimit << "\n";
    }
}

void printSessions(const vector<Sessions>& sessions) {
    for (auto& s : sessions) {
        cout << s.sid << " "
             << s.filmId << " "
             << s.date << " "
             << s.time << " "
             << s.hallId << " "
             << s.price << "\n";
    }
}

// add
void addFilm(vector<Films>& films) {
    Films f;

    cout << "ID: "; cin >> f.id;
    cout << "Name: "; cin >> f.name;
    cout << "Genre: "; cin >> f.genre;
    cout << "Duration: "; cin >> f.duration;
    cout << "Age limit: "; cin >> f.agelimit;

    films.push_back(f);
    saveFilms(films);
}

void addSession(vector<Sessions>& sessions) {
    Sessions s;

    cout << "SID: "; cin >> s.sid;
    cout << "Film ID: "; cin >> s.filmId;
    cout << "Date: "; cin >> s.date;
    cout << "Time: "; cin >> s.time;
    cout << "Hall ID: "; cin >> s.hallId;
    cout << "Price: "; cin >> s.price;

    sessions.push_back(s);
    saveSessions(sessions);
}

// delete
void deleteFilm(vector<Films>& films) {
    string name;
    cout << "Film name: ";
    cin >> name;

    for (int i = 0; i < films.size(); i++) {
        if (films[i].name == name) {
            films.erase(films.begin() + i);
            break;
        }
    }

    saveFilms(films);
}

void deleteSession(vector<Sessions>& sessions) {
    int sid;
    cout << "Session ID: ";
    cin >> sid;

    for (int i = 0; i < sessions.size(); i++) {
        if (sessions[i].sid == sid) {
            sessions.erase(sessions.begin() + i);
            break;
        }
    }

    saveSessions(sessions);
}

// edit

void editFilm(vector<Films>& films) {
    string name;
    cout << "Film name: ";
    cin >> name;

    for (auto& f : films) {
        if (f.name == name) {
            cout << "New ID: "; cin >> f.id;
            cout << "New name: "; cin >> f.name;
            cout << "New genre: "; cin >> f.genre;
            cout << "New duration: "; cin >> f.duration;
            cout << "New age limit: "; cin >> f.agelimit;
            break;
        }
    }

    saveFilms(films);
}

void editSession(vector<Sessions>& sessions) {
    int sid;
    cout << "Session ID: ";
    cin >> sid;

    for (auto& s : sessions) {
        if (s.sid == sid) {
            cout << "New SID: "; cin >> s.sid;
            cout << "New Film ID: "; cin >> s.filmId;
            cout << "New date: "; cin >> s.date;
            cout << "New time: "; cin >> s.time;
            cout << "New hall ID: "; cin >> s.hallId;
            cout << "New price: "; cin >> s.price;
            break;
        }
    }

    saveSessions(sessions);
}

// menu

void runMenu(vector<Films>& films, vector<Sessions>& sessions) {
    int choice;

    while (true) {
        cout << "\n1 Films\n2 Sessions\n3 Add film\n4 Add session\n"
             << "5 Delete film\n6 Delete session\n7 Edit film\n8 Edit session\n0 Exit\n> ";

        cin >> choice;

        switch (choice) {
            case 1: printFilms(films); break;
            case 2: printSessions(sessions); break;
            case 3: addFilm(films); break;
            case 4: addSession(sessions); break;
            case 5: deleteFilm(films); break;
            case 6: deleteSession(sessions); break;
            case 7: editFilm(films); break;
            case 8: editSession(sessions); break;
            case 0: return;
            default: cout << "Wrong choice\n";
        }
    }
}