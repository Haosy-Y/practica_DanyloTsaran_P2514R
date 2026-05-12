#include "functions.h"
#include "menu.h"

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

void printFilms(const vector<Films>& films) {
    const int wId = 6, wName = 52, wGenre = 24, wDuration = 10, wRating = 10;
    const int lineW = wId + wName + wGenre + wDuration + wRating;

    cout << left
         << setw(wId) << "ID"
         << setw(wName) << "Name"
         << setw(wGenre) << "Genre"
         << setw(wDuration) << "Duration"
         << setw(wRating) << "Rating" << "\n";
    cout << string(lineW, '-') << "\n";

    for (const auto& f : films) {
        cout << left
             << setw(wId) << f.id
             << setw(wName) << f.name
             << setw(wGenre) << f.genre
             << setw(wDuration) << f.duration
             << setw(wRating) << f.agelimit << "\n";
    }
}

void printSessions(const vector<Sessions>& sessions) {
    const int wSid = 8, wFilmId = 8, wDate = 12, wTime = 8, wHall = 5, wPrice = 8;
    const int lineW = wSid + wFilmId + wDate + wTime + wHall + wPrice;

    cout << left
         << setw(wSid) << "SID"
         << setw(wFilmId) << "FilmID"
         << setw(wDate) << "Date"
         << setw(wTime) << "Time"
         << setw(wHall) << "Hall"
         << setw(wPrice) << "Price" << "\n";
    cout << string(lineW, '-') << "\n";

    for (const auto& s : sessions) {
        cout << left
             << setw(wSid) << s.sid
             << setw(wFilmId) << s.filmId
             << setw(wDate) << s.date
             << setw(wTime) << s.time
             << setw(wHall) << s.hallId
             << setw(wPrice) << s.price << "\n";
    }
}

void printListings(int kind, const vector<Films>& films, const vector<Sessions>& sessions) {
    if (kind == 1) {
        printFilms(films);
        return;
    }
    if (kind == 2) {
        printSessions(sessions);
        return;
    }
    cout << RED "Неверный тип списка для вывода.\n" RESET;
}

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
        cout << RED "Не добавлено: ошибка в формате.\n" RESET;
        return;
    }

    for (const auto& ex : films)
        if (ex.id == f.id) {
            cout << RED "Не добавлено: фильм с таким ID уже существует.\n" RESET;
            return;
        }

    films.push_back(f);
    saveFilms(films);
    cout << GREEN "Успешно: фильм добавлен.\n" RESET;
}

void addSession(vector<Sessions>& sessions, const vector<Films>& films) {
    Sessions s;
    cout << "Айди сессии: ";  cin >> s.sid;
    cout << "Айди фильма: ";  cin >> s.filmId;
    cin.ignore();
    cout << "Дата: ";         getline(cin, s.date);
    cout << "Время: ";        getline(cin, s.time);
    cout << "Номер зала: ";   cin >> s.hallId;
    cout << "Цена: ";         cin >> s.price;

    if (!patternSession(s)) {
        cout << RED "Не добавлено: ошибка в формате.\n" RESET;
        return;
    }

    for (const auto& ex : sessions)
        if (ex.sid == s.sid) {
            cout << RED "Не добавлено: сессия с таким ID уже существует.\n" RESET;
            return;
        }
    sessions.push_back(s);
    saveSessions(sessions);
    cout << GREEN "Успешно: сессия добавлена.\n" RESET;
}

void deleteFilm(vector<Films>& films) {
    string name;
    cout << "Название фильма: ";
    cin.ignore();
    getline(cin, name);

    for (int i = 0; i < (int)films.size(); i++) {
        if (films[i].name == name) {
            films.erase(films.begin() + i);
            cout << GREEN "Успешно: фильм удалён.\n" RESET;
            saveFilms(films);
            return;
        }
    }
    cout << RED "Не успешно: фильм не найден.\n" RESET;
}

void deleteSession(vector<Sessions>& sessions) {
    int sid;
    cout << "Айди сессии: "; cin >> sid;

    for (int i = 0; i < (int)sessions.size(); i++) {
        if (sessions[i].sid == sid) {
            sessions.erase(sessions.begin() + i);
            cout << GREEN "Успешно: сессия удалена.\n" RESET;
            saveSessions(sessions);
            return;
        }
    }
    cout << RED "Не успешно: сессия не найдена.\n" RESET;
}

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
                cout << RED "Не обновлено: ошибка в формате.\n" RESET;
                return;
            }

            f = updated;
            break;
        }
    }
    if (found) {
        saveFilms(films);
        cout << GREEN "Успешно: фильм обновлён.\n" RESET;
    } else {
        cout << RED "Не успешно: фильм не найден.\n" RESET;
    }
}

void editSession(vector<Sessions>& sessions, const vector<Films>& films) {
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
                cout << RED "Не обновлено: ошибка в формате.\n" RESET;
                return;
            }

            s = updated;
            break;
        }
    }
    if (found) {
        saveSessions(sessions);
        cout << GREEN "Успешно: сессия обновлена.\n" RESET;
    } else {
        cout << RED "Не успешно: сессия не найдена.\n" RESET;
    }
}

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
        cout << RED "Не успешно: не найдено сессий на указанную дату " << date << ".\n" RESET;
        return;
    }

    ofstream file("today.txt", ios::trunc);
    int written = 0;
    struct TodayRow {
        string time;
        string name;
        string genre;
        string duration;
        string rating;
        int hallId;
        int price;
    };
    vector<TodayRow> consoleRows;
    for (const auto& s : todaySessions) {
        for (const auto& f : films) {
            if (f.id == s.filmId) {
                file << s.time << "|"
                     << f.name << "|"
                     << f.genre << "|"
                     << f.duration << "|"
                     << f.agelimit << "|"
                     << s.hallId << "|"
                     << s.price << "\n";
                consoleRows.push_back({s.time, f.name, f.genre, f.duration, f.agelimit, s.hallId, s.price});
                written++;
                break;
            }
        }
    }
    file.close();

    cout << GREEN "Успешно: файл today.txt создан.\n" RESET;
    if (written == 0) {
        cout << RED "На эту дату сеансы есть, но ни один не связан с фильмом по id.\n" RESET;
        return;
    }
    const int wTime = 8, wName = 52, wGenre = 24, wDuration = 10, wRating = 10, wHall = 5, wPrice = 8;
    const int lineW = wTime + wName + wGenre + wDuration + wRating + wHall + wPrice;

    cout << BLUE "Сеансы на дату " << date << ":\n" RESET;
    cout << left
         << setw(wTime) << "Time"
         << setw(wName) << "Name"
         << setw(wGenre) << "Genre"
         << setw(wDuration) << "Duration"
         << setw(wRating) << "Rating"
         << setw(wHall) << "Hall"
         << setw(wPrice) << "Price" << "\n";
    cout << string(lineW, '-') << "\n";

    for (const auto& row : consoleRows) {
        cout << left
             << setw(wTime) << row.time
             << setw(wName) << row.name
             << setw(wGenre) << row.genre
             << setw(wDuration) << row.duration
             << setw(wRating) << row.rating
             << setw(wHall) << row.hallId
             << setw(wPrice) << row.price << "\n";
    }
}

void sortPrint(const vector<Films>& films) {
    vector<Films> tmp = films;

    for (int i = 0; i < (int)tmp.size() - 1; i++)
        for (int j = 0; j < (int)tmp.size() - i - 1; j++)
            if (tmp[j].name > tmp[j+1].name)
                swap(tmp[j], tmp[j+1]);

    const int wId = 6, wName = 52, wGenre = 24, wDuration = 10, wRating = 10;
    const int lineW = wId + wName + wGenre + wDuration + wRating;

    cout << BLUE "\nФильмы в алфавитном порядке:\n" RESET;
    cout << left
         << setw(wId) << "ID"
         << setw(wName) << "Name"
         << setw(wGenre) << "Genre"
         << setw(wDuration) << "Duration"
         << setw(wRating) << "Rating" << "\n";
    cout << string(lineW, '-') << "\n";

    for (const auto& f : tmp) {
        cout << left
             << setw(wId) << f.id
             << setw(wName) << f.name
             << setw(wGenre) << f.genre
             << setw(wDuration) << f.duration
             << setw(wRating) << f.agelimit << "\n";
    }
}

static string genreByFilmId(const vector<Films>& films, int filmId) {
    for (const auto& f : films) {
        if (f.id == filmId)
            return f.genre;
    }
    return "";
}

void printMostPopularGenre(const vector<Films>& films, const vector<Sessions>& sessions) {
    map<string, int> sessionsPerGenre;
    for (const auto& s : sessions) {
        string g = genreByFilmId(films, s.filmId);
        if (!g.empty())
            sessionsPerGenre[g]++;
    }

    if (sessionsPerGenre.empty()) {
        cout << RED "Нет данных: нет сеансов или не найдены фильмы по id.\n" RESET;
        return;
    }

    int best = 0;
    for (const auto& p : sessionsPerGenre)
        if (p.second > best)
            best = p.second;

    cout << GREEN "Самый популярный жанр по числу сеансов: максимум " << best << " сеанс(ов).\n" RESET;
    for (const auto& p : sessionsPerGenre) {
        if (p.second == best)
            cout << "  " << p.first << " — " << p.second << "\n";
    }
}

void printAverageTicketForGenre(const vector<Films>& films, const vector<Sessions>& sessions) {
    string genre;
    cout << "Жанр (как в каталоге фильмов): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, genre);

    long long sum = 0;
    int n = 0;
    for (const auto& s : sessions) {
        if (genreByFilmId(films, s.filmId) == genre) {
            sum += s.price;
            n++;
        }
    }

    if (n == 0) {
        cout << RED "Нет сеансов для жанра \"" << genre << "\".\n" RESET;
        return;
    }

    stringstream ss;
    ss << fixed << setprecision(2) << (double)sum / n;
    cout << GREEN "Средняя стоимость билета: " << ss.str() << "\n" RESET;
}

