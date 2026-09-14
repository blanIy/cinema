#include "cinema.h"
#include <iostream>

struct TicketPurchase {
    std::string movieTitle;
    std::string day;
    std::string time;
    bool isVip = false;
    int count = 0;
    double price = 0.0;
};
struct MyCart {
    std::vector<TicketPurchase> purchases;
    double totalSpent = 0.0;
};

void printMenuOptions() {
    std::cout << "\n========================================\n";
    std::cout << "           КИНОТЕАТР \"ЗВЕЗДА\"           \n";
    std::cout << "========================================\n";
    std::cout << "1. Показать афишу сеансов\n";
    std::cout << "2. Купить билеты (Выбор дня и фильма)\n";
    std::cout << "3. Мой личный кабинет / Корзина покупок\n";
    std::cout << "4. Выйти из кинотеатра\n";
    std::cout << "========================================\n";
    std::cout << "Выберите действие (1-4): ";
}

void handleTicketPurchase(Cinema& myCinema, MyCart& cart) {
    std::cout << "\n--- ШАГ 1: Выберите день недели ---\n";
    std::cout << "1. Пятница\n2. Суббота\n3. Воскресенье\n";
    std::cout << "Ваш выбор (1-3): ";
    int dChoice = 0;
    if (!(std::cin >> dChoice) || dChoice < 1 || dChoice > 3) {
        std::cout << "\nОшибка: Некорректный выбор дня!\n";
        std::cin.clear(); std::cin.ignore(10000, '\n'); return;
    }
    std::string days[] = { "Пятница", "Суббота", "Воскресенье" };
    std::string selectedDay = days[dChoice - 1];
    auto available = myCinema.getSessionsByDay(selectedDay);
    if (available.empty()) {
        std::cout << "\nК сожалению, на " << selectedDay << " сеансов нет.\n";
        return;
    }

    std::cout << "\n--- ШАГ 2: Доступные сеансы на день [" << selectedDay << "] ---\n";
    const auto availableCount = static_cast<int>(available.size());
    for (auto i = 0; i < availableCount; ++i) {
        if (const auto* s = available[i]; s != nullptr) {
            std::cout << (i + 1) << ". \"" << s->getMovieTitle() << "\" в " << s->getStartTime()
                << " [Обычные: " << s->getAvailableRegularSeats() << "/" << s->getTotalRegularSeats()
                << " | VIP: " << s->getAvailableVipSeats() << "/" << s->getTotalVipSeats() << "]\n";
        }
    }
    std::cout << "Выберите сеанс (1-" << availableCount << "): ";
    int sChoice = 0;
    if (!(std::cin >> sChoice) || sChoice < 1 || sChoice > availableCount) {
        std::cout << "\nОшибка: Неверный выбор сеанса!\n";
        std::cin.clear(); std::cin.ignore(10000, '\n'); return;
    }
    const auto* chosenSession = available[sChoice - 1];
    std::cout << "\n--- ШАГ 3: Выберите класс места ---\n";
    std::cout << "1. Обычное место (цена: 12.00 руб.)\n";
    std::cout << "2. VIP место     (цена: 25.00 руб.)\n";
    std::cout << "Ваш выбор (1-2): ";
    int typeChoice = 0;
    if (!(std::cin >> typeChoice) || typeChoice < 1 || typeChoice > 2) {
        std::cout << "\nОшибка: Некорректный выбор класса билета!\n";
        std::cin.clear(); std::cin.ignore(10000, '\n'); return;
    }
    bool isVip = (typeChoice == 2);

    std::cout << "\n--- ШАГ 4: Введите количество билетов ---\n";
    std::cout << "Сколько билетов вы хотите купить? ";
    int tickets = 0;
    if (!(std::cin >> tickets) || tickets <= 0) {
        std::cout << "\nОшибка: Введено некорректное количество билетов!\n";
        std::cin.clear(); std::cin.ignore(10000, '\n'); return;
    }

    if (chosenSession != nullptr) {
        std::string title = chosenSession->getMovieTitle();
        std::string time = chosenSession->getStartTime();

        if (myCinema.buyTicketForSession(title, selectedDay, time, isVip, tickets)) {
            double price = isVip ? 25.00 : 12.00;
            cart.totalSpent += (tickets * price);
            cart.purchases.push_back({ title, selectedDay, time, isVip, tickets, price });

            std::cout << "\nУспешно! Вы приобрели билеты в количестве " << tickets << " шт.\n";
        }
        else {
            int availableSeats = isVip ? chosenSession->getAvailableVipSeats() : chosenSession->getAvailableRegularSeats();
            std::cout << "\nОшибка: Мест выбранного класса недостаточно! Доступно свободных: " << availableSeats << ".\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    Cinema myCinema("Звезда");
    MyCart myCart;
    myCinema.addSession(Session("Начало", "Триллер", "Пятница", "15:00", 20, 5));
    myCinema.addSession(Session("Дюна", "Фантастика", "Пятница", "18:00", 15, 2));
    myCinema.addSession(Session("Матрица", "Боевик", "Пятница", "21:00", 30, 8));

    myCinema.addSession(Session("Интерстеллар", "Научная фантастика", "Суббота", "18:00", 40, 10));
    myCinema.addSession(Session("Аватар", "Приключения", "Суббота", "21:00", 15, 4));

    myCinema.addSession(Session("Дюна", "Фантастика", "Воскресенье", "15:00", 10, 2));
    myCinema.addSession(Session("Интерстеллар", "Научная фантастика", "Воскресенье", "18:00", 50, 12));

    int choice = 0;

    while (true) {
        printMenuOptions();

        if (!(std::cin >> choice)) {
            std::cout << "\nОшибка: Пожалуйста, введите корректное число!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 4) {
            std::cout << "\nСпасибо за визит! До встречи в кинотеатре \"Звезда\"!\n";
            break;
        }

        switch (choice) {
        case 1:
            std::cout << "\n";
            myCinema.showSchedule();
            break;
        case 2:
            handleTicketPurchase(myCinema, myCart);
            break;
        case 3:
            std::cout << "\n=== Мой личный кабинет ===\n";
            if (myCart.purchases.empty()) {
                std::cout << "История покупок пуста. Вы еще не приобрели ни одного билета.\n";
            }
            else {
                std::cout << "Детализированная история ваших покупок:\n";
                for (const auto& purchase : myCart.purchases) {
                    std::cout << "- Фильм: \"" << purchase.movieTitle << "\" | "
                        << purchase.day << " в " << purchase.time << "\n"
                        << "  Класс места: " << (purchase.isVip ? "VIP" : "Обычный")
                        << " | Билетов: " << purchase.count << " шт."
                        << " | На сумму: " << (purchase.count * purchase.price) << " руб.\n";
                }
            }
            std::cout << "---------------------------\n";
            std::cout << "Итоговая сумма покупок: " << myCart.totalSpent << " руб.\n";
            std::cout << "===========================\n";
            break;
        default:
            std::cout << "\nОшибка: Неверный пункт меню! Выберите число от 1 до 4.\n";
            break;
        }
    }

    return 0;
}