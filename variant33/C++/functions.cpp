#include "functions.h"

// запись
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

// сохранение
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

// вывод
void printFilms(const vector<Films>& films) {
    for (auto& f : films)
        cout << f.id << " " << f.name << " " << f.genre << " " << f.duration << " " << f.agelimit << "\n";
}

void printSessions(const vector<Sessions>& sessions) {
    for (auto& s : sessions)
        cout << s.sid << " " << s.filmId << " " << s.date << " " << s.time << " " << s.hallId << " " << s.price << "\n";
}

// добавление
void addFilm(vector<Films>& films) {
    Films f;
    cout << "ID: "; cin >> f.id;
    cin.ignore();                                      // сбросить '\n' после cin >>
    cout << "Name: ";     getline(cin, f.name);
    cout << "Genre: ";    getline(cin, f.genre);
    cout << "Duration: "; getline(cin, f.duration);
    cout << "Age limit: "; getline(cin, f.agelimit);
    films.push_back(f);
    saveFilms(films);
}

void addSession(vector<Sessions>& sessions) {
    Sessions s;
    cout << "SID: ";     cin >> s.sid;
    cout << "Film ID: "; cin >> s.filmId;
    cin.ignore();
    cout << "Date: ";    getline(cin, s.date);
    cout << "Time: ";    getline(cin, s.time);
    cout << "Hall ID: "; cin >> s.hallId;
    cout << "Price: ";   cin >> s.price;
    sessions.push_back(s);
    saveSessions(sessions);
}

// удаление
void deleteFilm(vector<Films>& films) {
    string name;
    cout << "Film name: ";
    cin.ignore();                                      // ключевой фикс
    getline(cin, name);                                // теперь читает "The Usual Suspects" целиком

    for (int i = 0; i < (int)films.size(); i++) {
        if (films[i].name == name) {
            films.erase(films.begin() + i);
            cout << "Фильм удалён.\n";
            saveFilms(films);
            return;
        }
    }
    cout << "Фильм не найден.\n";
}

void deleteSession(vector<Sessions>& sessions) {
    int sid;
    cout << "Session ID: "; cin >> sid;

    for (int i = 0; i < (int)sessions.size(); i++) {
        if (sessions[i].sid == sid) {
            sessions.erase(sessions.begin() + i);
            cout << "Сессия удалена.\n";
            saveSessions(sessions);
            return;
        }
    }
    cout << "Сессия не найдена.\n";
}

// редактирование
void editFilm(vector<Films>& films) {
    string name;
    cout << "Film name: ";
    cin.ignore();
    getline(cin, name);

    for (auto& f : films) {
        if (f.name == name) {
            cout << "New ID: "; cin >> f.id;
            cin.ignore();
            cout << "New name: ";     getline(cin, f.name);
            cout << "New genre: ";    getline(cin, f.genre);
            cout << "New duration: "; getline(cin, f.duration);
            cout << "New age limit: "; getline(cin, f.agelimit);
            break;
        }
    }
    saveFilms(films);
}

void editSession(vector<Sessions>& sessions) {
    int sid;
    cout << "Session ID: "; cin >> sid;

    for (auto& s : sessions) {
        if (s.sid == sid) {
            cout << "New SID: ";     cin >> s.sid;
            cout << "New Film ID: "; cin >> s.filmId;
            cin.ignore();
            cout << "New date: ";    getline(cin, s.date);
            cout << "New time: ";    getline(cin, s.time);
            cout << "New hall ID: "; cin >> s.hallId;
            cout << "New price: ";   cin >> s.price;
            break;
        }
    }
    saveSessions(sessions);
}

// иное
void createTodayFile(const vector<Films>& films, const vector<Sessions>& sessions) {
    string date;
    cout << "Введите дату (YYYY-MM-DD): ";
    cin >> date;

    // Найти сессии на указанную дату
    vector<Sessions> todaySessions;
    for (const auto& s : sessions) {
        if (s.date == date) {
            todaySessions.push_back(s);
        }
    }

    if (todaySessions.empty()) {
        cout << "Не найдено сессии на указанную Дату." << date << "\n";
        return;
    }

    ofstream file("today.txt");
    file << "Фильмы в данную дату : " << date << ":\n";
    file << string(50, '-') << "\n";
    file << "Данные указаны в таком формате : " << ":\n";
    file << "Время | Название | Жанр | Длительность | Рейтинг | Номер зала | Цена" << "\n";
    file << string(50, '-') << "\n" << "\n";
    for (const auto& s : todaySessions) {
        // Найти фильм по filmId
        for (const auto& f : films) {
            if (f.id == s.filmId) {
                file << s.time << " | " << f.name << " | " << f.genre << " | " 
                << f.duration << " | " << f.agelimit << " | " << s.hallId << " | " 
                << s.price << "\n" << string(50, '-') << "\n";
                break;
            }
        }
    }

    cout << "today.txt создан коректно!\n";
}

void sortPrint(const vector<Films>& films) {
    vector<Films> tmp = films;

    for (int i = 0; i < tmp.size() - 1; i++)
        for (int j = 0; j < tmp.size() - i - 1; j++)
            if (tmp[j].name > tmp[j+1].name)
                swap(tmp[j], tmp[j+1]);

    cout << "\nФильмы в алфавитном порядке:\n";
    for (const auto& f : tmp)
        cout << f.name << " | " << f.id << " | " << f.genre << " | "
             << f.duration << " | " << f.agelimit << "\n";
    cout << "\nДанные указаны в таком формате : " << "\n";
    cout << "Название | Айди  |  Жанр | Длительность | Возрастной рейтинг" << "\n";
}

static bool postActionMenu() {
    cout << "\n--- Что дальше? ---\n1 Вернуться в меню\n0 Выход\n> ";
    int c; cin >> c;
    return c != 0;
}

void runMenu(vector<Films>& films, vector<Sessions>& sessions) {
    int choice;
    while (true) {
        cout << "\n1 Список фильмов\n2 Список сессий\n3 Добавить фильм\n4 Добавить сессию\n"
             << "5 Удалить фильм\n6 Удалить сессию\n7 Редактировать фильмы\n8 Редактировать сессии\n"
             << "9 Создать today.txt\n10 Сортировка фильмов\n0 Выход\n> ";
        cin >> choice;

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[!] Некорректный ввод. Введите число от 0 до 10.\n";
            continue;
        }

        if (choice == 0) return;

        switch (choice) {
            case 1:  printFilms(films);               break;
            case 2:  printSessions(sessions);         break;
            case 3:  addFilm(films);                  break;
            case 4:  addSession(sessions);            break;
            case 5:  deleteFilm(films);               break;
            case 6:  deleteSession(sessions);         break;
            case 7:  editFilm(films);                 break;
            case 8:  editSession(sessions);           break;
            case 9:  createTodayFile(films, sessions); break;
            case 10: sortPrint(films);                break;
            default: cout << "Нету такого варианта\n"; continue;
        }

        if (!postActionMenu()) return;
    }
}
