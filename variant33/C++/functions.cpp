#include "functions.h"

static bool patternFilm(const Films& f) {
    if (f.id <= 0) return false;
    if (f.name.empty() || f.genre.empty() || f.duration.empty() || f.agelimit.empty()) return false;

    static const vector<string> allowedRatings = {"G", "PG", "PG-13", "R", "NC-17"};
    bool ratingOk = false;
    for (const auto& r : allowedRatings) {
        if (f.agelimit == r) {
            ratingOk = true;
            break;
        }
    }
    if (!ratingOk) return false;

    return true;
}

static bool patternSession(const Sessions& s) {
    if (s.sid <= 0 || s.filmId <= 0 || s.hallId <= 0 || s.price <= 0) return false;

    static const regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
    static const regex timePattern(R"(^([01]\d|2[0-3]):[0-5]\d$)");
    if (!regex_match(s.date, datePattern)) return false;
    if (!regex_match(s.time, timePattern)) return false;

    return true;
}

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
    cout << "Формат: Айди(число) | Название(текст) | Жанр(текст) | Длительность(текст) | Рейтинг(G, PG, PG-13, R, NC-17)\n";
    cout << "Айди: "; cin >> f.id;
    cin.ignore();     
    cout << "Название: ";     getline(cin, f.name);
    cout << "Жанр: ";    getline(cin, f.genre);
    cout << "Длительность: "; getline(cin, f.duration);
    cout << "Возрастной рейтинг: "; getline(cin, f.agelimit);

    if (!patternFilm(f)) {
        cout << "Не добавлено: ошибка в формате.\n";
        return;
    }

    films.push_back(f);
    saveFilms(films);
    cout << "Успешно: фильм добавлен.\n";
}

void addSession(vector<Sessions>& sessions) {
    Sessions s;
    cout << "Формат: Айди сессии(число) | Айди фильма(число) | Дата(YYYY-MM-DD) | Время(HH:MM) | Номер зала(число) | Цена(число)\n";
    cout << "Айди сессии: ";     cin >> s.sid;
    cout << "Айди фильма: "; cin >> s.filmId;
    cin.ignore();
    cout << "Дата: ";    getline(cin, s.date);
    cout << "Время: ";    getline(cin, s.time);
    cout << "Номер зала: "; cin >> s.hallId;
    cout << "Цена: ";   cin >> s.price;

    if (!patternSession(s)) {
        cout << "Не добавлено: ошибка в формате.\n";
        return;
    }

    sessions.push_back(s);
    saveSessions(sessions);
    cout << "Успешно: сессия добавлена.\n";
}

// удаление
void deleteFilm(vector<Films>& films) {
    string name;
    cout << "Название фильма: ";
    cin.ignore();
    getline(cin, name);

    for (int i = 0; i < (int)films.size(); i++) {
        if (films[i].name == name) {
            films.erase(films.begin() + i);
            cout << "Успешно: фильм удалён.\n";
            saveFilms(films);
            return;
        }
    }
    cout << "Не успешно: фильм не найден.\n";
}

void deleteSession(vector<Sessions>& sessions) {
    int sid;
    cout << "Айди сессии: "; cin >> sid;

    for (int i = 0; i < (int)sessions.size(); i++) {
        if (sessions[i].sid == sid) {
            sessions.erase(sessions.begin() + i);
            cout << "Успешно: сессия удалена.\n";
            saveSessions(sessions);
            return;
        }
    }
    cout << "Не успешно: сессия не найдена.\n";
}

// редактирование
void editFilm(vector<Films>& films) {
    string name;
    cout << "Название фильма: ";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (auto& f : films) {
        if (f.name == name) {
            found = true;
            Films updated = f;
            cout << "Формат: Айди(число) | Жанр(текст) | Длительность(текст) | Рейтинг(G, PG, PG-13, R, NC-17)\n";
            cout << "Название не меняется: " << updated.name << "\n";
            cout << "Новый айди: "; cin >> updated.id;
            cin.ignore();
            cout << "Новый жанр: ";    getline(cin, updated.genre);
            cout << "Новая длительность: "; getline(cin, updated.duration);
            cout << "Новый возрастной рейтинг: "; getline(cin, updated.agelimit);

            if (!patternFilm(updated)) {
                cout << "Не обновлено: ошибка в формате.\n";
                return;
            }

            f = updated;
            break;
        }
    }
    if (found) {
        saveFilms(films);
        cout << "Успешно: фильм обновлён.\n";
    } else {
        cout << "Не успешно: фильм не найден.\n";
    }
}

void editSession(vector<Sessions>& sessions) {
    int sid;
    cout << "Айди сессии: "; cin >> sid;

    bool found = false;
    for (auto& s : sessions) {
        if (s.sid == sid) {
            found = true;
            Sessions updated = s;
            cout << "Формат: Айди фильма(число) | Дата(YYYY-MM-DD) | Время(HH:MM) | Номер зала(число) | Цена(число)\n";
            cout << "Айди сессии не меняется: " << updated.sid << "\n";
            cout << "Новый айди фильма: "; cin >> updated.filmId;
            cin.ignore();
            cout << "Новая дата: ";    getline(cin, updated.date);
            cout << "Новое время: ";    getline(cin, updated.time);
            cout << "Новый номер зала: "; cin >> updated.hallId;
            cout << "Новая цена: ";   cin >> updated.price;

            if (!patternSession(updated)) {
                cout << "Не обновлено: ошибка в формате.\n";
                return;
            }

            s = updated;
            break;
        }
    }
    if (found) {
        saveSessions(sessions);
        cout << "Успешно: сессия обновлена.\n";
    } else {
        cout << "Не успешно: сессия не найдена.\n";
    }
}

// иное
void createTodayFile(const vector<Films>& films, const vector<Sessions>& sessions) {
    string date;
    cout << "Введите дату (YYYY-MM-DD): ";
    cin >> date;

    
    vector<Sessions> todaySessions;
    for (const auto& s : sessions) {
        if (s.date == date) {
            todaySessions.push_back(s);
        }
    }

    if (todaySessions.empty()) {
        cout << "Не успешно: не найдено сессий на указанную дату " << date << ".\n";
        return;
    }

    ofstream file("today.txt");
    file << "Фильмы в данную дату : " << date << ":\n";
    file << string(50, '-') << "\n";
    file << "Данные указаны в таком формате : " << ":\n";
    file << "Время | Название | Жанр | Длительность | Рейтинг | Номер зала | Цена" << "\n";
    file << string(50, '-') << "\n" << "\n";
    for (const auto& s : todaySessions) {
        for (const auto& f : films) {
            if (f.id == s.filmId) {
                file << s.time << " | " << f.name << " | " << f.genre << " | " 
                << f.duration << " | " << f.agelimit << " | " << s.hallId << " | " 
                << s.price << "\n" << string(50, '-') << "\n";
                break;
            }
        }
    }

    cout << "Успешно: today.txt создан корректно.\n";
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
    while (true) {
        cout << "\n--- Что дальше? ---\n1 Вернуться в меню\n0 Выход\n> ";
        int c;
        if (!(cin >> c)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверное значение. Введите только 1 или 0.\n";
            continue;
        }
        if (c == 1) return true;
        if (c == 0) return false;
        cout << "Неверное значение. Введите только 1 или 0.\n";
    }
}

void runMenu(vector<Films>& films, vector<Sessions>& sessions) {
    int choice;
    while (true) {
        cout << "\n1 Список фильмов\n2 Список сессий\n3 Добавить фильм\n4 Добавить сессию\n"
             << "5 Удалить фильм\n6 Удалить сессию\n7 Редактировать фильмы\n8 Редактировать сессии\n"
             << "9 Создать today.txt\n10 Сортировка фильмов\n0 Выход\n> ";
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
