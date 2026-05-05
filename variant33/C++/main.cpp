#include <bits/stdc++.h>
using namespace std;
struct Films {
    int id;
    string name, genre;
    time_t duration;
    string agelimit;
};

int main() {
    ifstream file("movie.txt");
    Films s[100];
    int n = 0;

    while(file >> s[n].id >> s[n].name >> s[n].genre >> s[n].duration >> s[n].agelimit) {
        
        n++;
    }
    return 0;
} 


