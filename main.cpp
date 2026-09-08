#include "cinema.h"
#include <iostream>

void printMenuOptions() {
    std::cout << "\n========================================\n";
    std::cout << "           МЕНЮ КИНОТЕАТРА              \n";
    std::cout << "========================================\n";
    std::cout << "1. Показать расписание сеансов\n";
    std::cout << "2. Купить билеты на сеанс\n";
    std::cout << "3. Выйти из программы\n";
    std::cout << "========================================\n";
    std::cout << "Выберите пункт меню (1-3): ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Инициализация данных — 5 разных фильмов с разным временем сеансов
    Cinema myCinema("Звезда");
    myCinema.addSession(Session("Дюна", "Фантастика", "15:00", 10));
    myCinema.addSession(Session("Интерстеллар", "Научная фантастика", "18:30", 50));
    myCinema.addSession(Session("Матрица", "Боевик", "21:00", 30));
    myCinema.addSession(Session("Начало", "Триллер", "12:00", 20));
    myCinema.addSession(Session("Аватар", "Приключения", "16:15", 15));

    int choice = 0;

    while (true) {
        printMenuOptions();

        // Защита от ввода букв вместо цифр
        if (!(std::cin >> choice)) {
            std::cout << "\nОшибка: Пожалуйста, введите корректное число!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 3) {
            std::cout << "\nВыход из программы. Освобождение ресурсов...\n";
            break;
        }

        switch (choice) {
        case 1:
            std::cout << "\n";
            myCinema.showSchedule();
            break;

        case 2: {
            int totalSessions = myCinema.getSessionCount();
            if (totalSessions == 0) {
                std::cout << "\nОшибка: Нет доступных сеансов!\n";
                break;
            }

            // Динамическое меню покупки: вычитывает все сеансы из кинотеатра
            std::cout << "\nВыберите фильм для покупки билетов:\n";
            for (int i = 0; i < totalSessions; ++i) {
                Session* s = myCinema.getSession(i);
                std::cout << (i + 1) << ". \"" << s->getMovieTitle()
                    << "\" [Время: " << s->getStartTime()
                    << " | Свободно: " << s->getAvailableSeats() << "]\n";
            }
            std::cout << "Ваш выбор (1-" << totalSessions << "): ";

            int movieChoice = 0;
            if (!(std::cin >> movieChoice) || movieChoice < 1 || movieChoice > totalSessions) {
                std::cout << "\nОшибка: Неверный выбор сеанса!\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                break;
            }

            std::cout << "Введите количество билетов: ";
            int tickets = 0;
            if (!(std::cin >> tickets) || tickets <= 0) {
                std::cout << "\nОшибка: Введено некорректное количество билетов!\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                break;
            }

            // Определяем название выбранного фильма по индексу
            std::string selectedMovie = myCinema.getSession(movieChoice - 1)->getMovieTitle();
            std::cout << "\n";
            myCinema.buyTicket(selectedMovie, tickets);
            break;
        }

        default:
            std::cout << "\nОшибка: Неверный пункт меню! Выберите число от 1 до 3.\n";
            break;
        }
    }

    return 0;
}