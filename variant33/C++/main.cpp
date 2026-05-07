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
    cout << "0. Выход\n";
    cout << "----------------------------------------\n";
    cout << "Ваш выбор: ";

    if (!(cin >> choice)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Неверный выбор. Введите число от 0 до 2.\n";
      continue;
    }

    switch (choice) {
    case 1:
      printFilms(films);
      break;
    case 2:
      printSessions(sessions);
      break;
    case 0:
      cout << "Выход из программы.\n";
      return;
    default:
      cout << "Неверный выбор. Введите число от 0 до 8.\n";
      break;
    }
  }
}

int main() {
  ifstream file1("x-movie.txt");
  ifstream file2("x-session.txt");
  if (!file1.is_open() || !file2.is_open()) {
    cout << "Ошибка: не удалось открыть movie.txt или session.txt\n";
    return 1;
  }

  vector<Films> films;
  vector<Sessions> sessions;

  Films film;
  while (file1 >> film.id >> film.name >> film.genre >> film.duration >>
         film.agelimit) {
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