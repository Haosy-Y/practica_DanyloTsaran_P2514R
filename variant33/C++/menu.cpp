#include "functions.h"
#include "menu.h"

void runMenu(vector<Films>& films, vector<Sessions>& sessions) {
    int choice;
    while (true) {
        cout << "\n" BLUE "=== Меню программы ===\n" RESET
             << BLUE   "[1]"  RESET " Список фильмов\n"
             << BLUE   "[2]"  RESET " Список сеансов\n"
             << GREEN  "[3]"  RESET " Добавить фильм\n"
             << GREEN  "[4]"  RESET " Добавить сеанс\n"
             << RED    "[5]"  RESET " Удалить фильм\n"
             << RED    "[6]"  RESET " Удалить сеанс\n"
             << YELLOW "[7]"  RESET " Редактировать фильмы\n"
             << YELLOW "[8]"  RESET " Редактировать сеансы\n"
             << BLUE   "[9]"  RESET " Создать файл и вывести его\n"
             << BLUE   "[10]" RESET " Сортировать фильмы по алфавиту\n"
             << BLUE   "[11]" RESET " Самый популярный жанр\n"
             << BLUE   "[12]" RESET " Средняя цена по жанру\n"
             << RED    "[0]"  RESET " Выход\n"
             << BLUE   "> "   RESET;

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED "[!] Некорректный ввод. Введите число от 0 до 12.\n" RESET;
            continue;
        }

        if (choice == 0) return;

        switch (choice) {
            case 1:
            case 2:
                printListings(choice, films, sessions);
                break;
            case 3:  addFilm(films);                              break;
            case 4:  addSession(sessions, films);                        break;
            case 5:  deleteFilm(films);                           break;
            case 6:  deleteSession(sessions);                     break;
            case 7:  editFilm(films);                             break;
            case 8:  editSession(sessions, films);                       break;
            case 9:  createTodayFile(films, sessions);            break;
            case 10: sortPrint(films);                            break;
            case 11: printMostPopularGenre(films, sessions);      break;
            case 12: printAverageTicketForGenre(films, sessions); break;
            default: cout << RED "Нету такого варианта\n" RESET;  continue;
        }
    }
}