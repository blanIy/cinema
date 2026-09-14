#include "cinema.h"
#include <iostream>

Session::Session(std::string_view title, std::string_view movieGenre, std::string_view time, int seats)
    : movieTitle(title), genre(movieGenre), startTime(time), totalSeats(seats) {
} 

std::string Session::getMovieTitle() const { return movieTitle; }
std::string Session::getGenre() const { return genre; }
std::string Session::getStartTime() const { return startTime; }
int Session::getTotalSeats() const { return totalSeats; }
int Session::getSoldSeats() const { return soldSeats; }
int Session::getAvailableSeats() const { return totalSeats - soldSeats; }

void Session::setStartTime(std::string_view newTime) {
    startTime = newTime;
}

bool Session::bookSeats(int count) {
    if (count <= 0) return false;
    if (soldSeats + count <= totalSeats) {
        soldSeats += count;
        return true;
    }
    return false;
}

void Session::printInfo() const {
    std::cout << "Фильм: \"" << movieTitle << "\" (" << genre << ")\n"
        << "Время начала: " << startTime << "\n"
        << "Всего мест: " << totalSeats << " | Продано: " << soldSeats
        << " | Свободно: " << getAvailableSeats() << "\n"
        << "----------------------------------------\n";
}
Cinema::Cinema(std::string_view cinemaName)
    : name(cinemaName) {
}

void Cinema::addSession(const Session& session) {
    sessions.push_back(session);
}

void Cinema::showSchedule() const {
    std::cout << "=== Расписание кинотеатра \"" << name << "\" ===\n\n";
    if (sessions.empty()) {
        std::cout << "Сеансов пока нет.\n";
        return;
    }
    for (const auto& session : sessions) {
        session.printInfo();
    }
}

void Cinema::buyTicket(std::string_view movieTitle, int seatCount) {
    std::cout << "Попытка покупки билетов (" << seatCount << " шт.) на фильм \"" << movieTitle << "\":\n";
    for (auto& session : sessions) {
        if (session.getMovieTitle() == movieTitle) {
            if (session.bookSeats(seatCount)) {
                std::cout << "Успешно! Билеты приобретены.\n\n";
            }
            else {
                std::cout << "Ошибка: Недостаточно свободных мест! Доступно всего: "
                    << session.getAvailableSeats() << ".\n\n";
            }
            return;
        }
    }
    std::cout << "Ошибка: Сеанс на фильм \"" << movieTitle << "\" не найден.\n\n";
}

int Cinema::getSessionCount() const {
    return static_cast<int>(sessions.size());
}

const Session* Cinema::getSession(int index) const {
    if (index >= 0 && index < static_cast<int>(sessions.size())) {
        return &sessions[index];
    }
    return nullptr;
}