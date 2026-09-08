#include "cinema.h"
#include <iostream>

// =================================================================
// Реализация методов класса Session
// =================================================================
Session::Session(std::string title, std::string movieGenre, std::string time, int seats)
    : movieTitle(title), genre(movieGenre), startTime(time), totalSeats(seats), soldSeats(0) {
}

std::string Session::getMovieTitle() const { return movieTitle; }
std::string Session::getGenre() const { return genre; }
std::string Session::getStartTime() const { return startTime; }
int Session::getTotalSeats() const { return totalSeats; }
int Session::getSoldSeats() const { return soldSeats; }
int Session::getAvailableSeats() const { return totalSeats - soldSeats; }

void Session::setStartTime(const std::string& newTime) {
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

// =================================================================
// Реализация методов класса Cinema
// =================================================================
Cinema::Cinema(std::string cinemaName)
    : name(cinemaName), count(0), capacity(2) {
    sessions = new Session * [capacity];
}

Cinema::~Cinema() {
    for (int i = 0; i < count; ++i) {
        delete sessions[i];
    }
    delete[] sessions;
}

Cinema::Cinema(const Cinema& other)
    : name(other.name), count(other.count), capacity(other.capacity) {
    sessions = new Session * [capacity];
    for (int i = 0; i < count; ++i) {
        sessions[i] = new Session(*other.sessions[i]);
    }
}

Cinema& Cinema::operator=(const Cinema& other) {
    if (this == &other) {
        return *this;
    }
    for (int i = 0; i < count; ++i) {
        delete sessions[i];
    }
    delete[] sessions;

    name = other.name;
    count = other.count;
    capacity = other.capacity;
    sessions = new Session * [capacity];
    for (int i = 0; i < count; ++i) {
        sessions[i] = new Session(*other.sessions[i]);
    }
    return *this;
}

void Cinema::resize() {
    capacity *= 2;
    Session** newSessions = new Session * [capacity];
    for (int i = 0; i < count; ++i) {
        newSessions[i] = sessions[i];
    }
    delete[] sessions;
    sessions = newSessions;
}

void Cinema::addSession(const Session& session) {
    if (count >= capacity) {
        resize();
    }
    sessions[count] = new Session(session);
    count++;
}

void Cinema::showSchedule() const {
    std::cout << "=== Расписание кинотеатра \"" << name << "\" ===\n\n";
    if (count == 0) {
        std::cout << "Сеансов пока нет.\n";
        return;
    }
    for (int i = 0; i < count; ++i) {
        sessions[i]->printInfo();
    }
}

void Cinema::buyTicket(const std::string& movieTitle, int seatCount) {
    std::cout << "Попытка покупки билетов (" << seatCount << " шт.) на фильм \"" << movieTitle << "\":\n";
    for (int i = 0; i < count; ++i) {
        if (sessions[i]->getMovieTitle() == movieTitle) {
            if (sessions[i]->bookSeats(seatCount)) {
                std::cout << "Успешно! Билеты приобретены.\n\n";
            }
            else {
                std::cout << "Ошибка: Недостаточно свободных мест! Доступно всего: "
                    << sessions[i]->getAvailableSeats() << ".\n\n";
            }
            return;
        }
    }
    std::cout << "Ошибка: Сеанс на фильм \"" << movieTitle << "\" не найден.\n\n";
}

// Новые геттеры
int Cinema::getSessionCount() const {
    return count;
}

Session* Cinema::getSession(int index) const {
    if (index >= 0 && index < count) {
        return sessions[index];
    }
    return nullptr;
}