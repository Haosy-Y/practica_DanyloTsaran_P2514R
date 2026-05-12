#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <bits/stdc++.h>
using namespace std;

struct Films {
    int id;
    string name;
    string genre;
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

// 
vector<Films> loadFilms();
vector<Sessions> loadSessions();
void saveFilms(const vector<Films>& films);
void printListings(int kind, const vector<Films>& films, const vector<Sessions>& sessions);
void addFilm(vector<Films>& films);
void addSession(vector<Sessions>& sessions, const vector<Films>& films);
void deleteFilm(vector<Films>& films);
void deleteSession(vector<Sessions>& sessions);
void editFilm(vector<Films>& films);
void editSession(vector<Sessions>& sessions, const vector<Films>& films);
void createTodayFile(const vector<Films>& films, const vector<Sessions>& sessions);
void sortPrint(const vector<Films>& films);
void printMostPopularGenre(const vector<Films>& films, const vector<Sessions>& sessions);
void printAverageTicketForGenre(const vector<Films>& films, const vector<Sessions>& sessions);

#endif