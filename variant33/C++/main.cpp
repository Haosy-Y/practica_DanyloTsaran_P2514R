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

void printFilms(vector<Films> films) {
  for (int i = 0; i < films.size(); i++) {
    cout << films[i].id << " " << films[i].name << " " << films[i].genre << " "
         << films[i].duration << " " << films[i].agelimit << endl;
  }
}

void printSessions(vector<Sessions> sessions) {
  for (int i = 0; i < sessions.size(); i++) {
    cout << sessions[i].sid << " " << sessions[i].filmId << " "
         << sessions[i].date << " " << sessions[i].time << " "
         << sessions[i].hallId << " " << sessions[i].price << endl;
  }
}

void addFilm(vector<Films> &films, Films film) {
  cout << "Введите фильм в формате: id name genre h:mm:ss ageLimit\n";
  cout << "Пример: 1 The_Shawshank_Redemption Prison_Drama 2:22:25 R\n";

  string line;
  getline(cin >> ws, line);

  regex fullPattern(
      R"(^([0-9]+)\s+(\S+)\s+(\S+)\s+([0-9]{1,2}:[0-9]{2}:[0-9]{2})\s+(G|PG|PG-13|R|NC-17)$)");
  smatch match;
  if (!regex_match(line, match, fullPattern)) {
    cout << "Фильм не добавлен - неверный формат" << endl;
    return;
  }

  film.id = stoi(match[1].str());
  film.name = match[2].str();
  film.genre = match[3].str();
  film.duration = match[4].str();
  film.agelimit = match[5].str();

  int h, m, s;
  char c1, c2;
  stringstream ss(film.duration);
  ss >> h >> c1 >> m >> c2 >> s;
  if (ss.fail() || c1 != ':' || c2 != ':' || m > 59 || s > 59) {
    cout << "Фильм не добавлен - неверный формат" << endl;
    return;
  }
  if (any_of(films.begin(), films.end(), [&](const Films &f) { return f.id == film.id; })) { cout << "Фильм не добавлен - id уже существует" << endl; return; }
  cout << "Фильм добавлен" << endl;
  films.push_back(film);
}

void addSession(vector<Sessions> &sessions, Sessions session) {
  cout << "Введите сеанс в формате: sid filmId date time hallId price\n";
  cout << "Пример: 1 1 2024-01-01 12:00 1 100\n";

  string line;
  getline(cin >> ws, line);

  regex fullPattern(
      R"(^([0-9]+)\s+([0-9]+)\s+([0-9]{4}-[0-9]{2}-[0-9]{2})\s+([0-9]{2}:[0-9]{2})\s+([0-9]+)\s+([0-9]+)$)");
  smatch match;
  if (!regex_match(line, match, fullPattern)) {
    cout << "Сеанс не добавлен - неверный формат" << endl;
    return;
  }

  session.sid = stoi(match[1].str());
  session.filmId = stoi(match[2].str());
  session.date = match[3].str();
  session.time = match[4].str();
  session.hallId = stoi(match[5].str());
  session.price = stoi(match[6].str());

  if (any_of(sessions.begin(), sessions.end(), [&](const Sessions &s) { return s.sid == session.sid; })) { cout << "Сеанс не добавлен - sid уже существует" << endl; return; }
  cout << "Сеанс добавлен" << endl;
  sessions.push_back(session);
}

void deleteFilm(vector<Films> &films) {
  cout << "Введите название фильма для удаления: ";
  string filmName;
  cin >> filmName;

  auto it = remove_if(films.begin(), films.end(),
                      [&](const Films &film) { return film.name == filmName; });

  if (it == films.end()) {
    cout << "Фильм с таким названием не найден" << endl;
    return;
  }

  films.erase(it, films.end());
  cout << "Фильм удален" << endl;
}

void deleteSession(vector<Sessions> &sessions) {
  cout << "Введите номер сеанса: ";
  int sidToDelete;
  if (!(cin >> sidToDelete)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Неверно, попробуйте иначе." << endl;
    return;
  }

  auto it = remove_if(sessions.begin(), sessions.end(),
                      [&](const Sessions &s) { return s.sid == sidToDelete; });
  int removed = (int)(sessions.end() - it);

  if (removed == 0) {
    cout << "Неверно, попробуйте иначе." << endl;
    return;
  }

  sessions.erase(it, sessions.end());
  cout << "Удалено сеансов: " << removed << endl;
}

void runMenu(vector<Films> &films, vector<Sessions> &sessions) {
  int choice;
  Films film;
  Sessions session;

  while (true) {
    cout << "\n========================================\n";
    cout << "            МЕНЮ КИНОТЕАТРА\n";
    cout << "========================================\n";
    cout << "1. Показать все фильмы\n";
    cout << "2. Показать все сеансы\n";
    cout << "3. Добавить новый фильм\n";
    cout << "4. Добавить новый сеанс\n";
    cout << "5. Удалить фильм по названию\n";
    cout << "6. Удалить сеанс по порядковому номеру\n";
    cout << "0. Выход\n";
    cout << "----------------------------------------\n";
    cout << "Ваш выбор: ";

    if (!(cin >> choice)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Неверный выбор. Введите число от 0 до 6.\n";
      continue;
    }

    switch (choice) {
    case 1:
      printFilms(films);
      break;
    case 2:
      printSessions(sessions);
      break;
    case 3:
      addFilm(films, film);
      break;
    case 4:
      addSession(sessions, session);
      break;
    case 5:
      deleteFilm(films);
      break;
    case 6:
      deleteSession(sessions);
      break;
    case 0:
      cout << "Выход из программы.\n";
      return;
    default:
      cout << "Неверный выбор. Введите число от 0 до 6.\n";
      break;
    }
  }
}

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
  while (file2 >> session.sid >> session.filmId >> session.date >>
         session.time >> session.hallId >> session.price) {
    sessions.push_back(session);
  }
  runMenu(films, sessions);

  return 0;
}