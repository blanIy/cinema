#include "cinema.h"
#include <iostream>

Session::Session(std::string_view title, std::string_view movieGenre, std::string_view sessionDate,
    std::string_view time, int regularSeats, int vipSeats)
    : movieTitle(title), genre(movieGenre), date(sessionDate), startTime(time),
    totalRegularSeats(regularSeats), totalVipSeats(vipSeats) {
}

std::string Session::getMovieTitle() const { return movieTitle; }
std::string Session::getGenre() const { return genre; }
std::string Session::getStartTime() const { return startTime; }
std::string Session::getDate() const { return date; }

int Session::getAvailableRegularSeats() const { return totalRegularSeats - soldRegularSeats; }
int Session::getAvailableVipSeats() const { return totalVipSeats - soldVipSeats; }
int Session::getTotalRegularSeats() const { return totalRegularSeats; }
int Session::getTotalVipSeats() const { return totalVipSeats; }

void Session::setStartTime(std::string_view newTime) {
    startTime = newTime;
}

bool Session::bookRegularSeats(int count) {
    if (count <= 0) return false;
    if (soldRegularSeats + count <= totalRegularSeats) {
        soldRegularSeats += count;
        return true;
    }
    return false;
}

bool Session::bookVipSeats(int count) {
    if (count <= 0) return false;
    if (soldVipSeats + count <= totalVipSeats) {
        soldVipSeats += count;
        return true;
    }
    return false;
}

void Session::printInfo() const {
    std::cout << "Фильм: \"" << movieTitle << "\" (" << genre << ")\n"
        << "Сеанс: " << date << " в " << startTime << "\n"
        << "Обычные места: свободно " << getAvailableRegularSeats() << " из " << totalRegularSeats << "\n"
        << "VIP места:     свободно " << getAvailableVipSeats() << " из " << totalVipSeats << "\n"
        << "----------------------------------------\n";
}

Cinema::Cinema(std::string_view cinemaName) : name(cinemaName) {}

void Cinema::addSession(const Session& session) {
    sessions.push_back(session);
}

void Cinema::showSchedule() const {
    std::cout << "=== Текущая афиша кинотеатра \"" << name << "\" ===\n\n";
    if (sessions.empty()) {
        std::cout << "Сеансов пока нет.\n";
        return;
    }
    for (const auto& s : sessions) {
        s.printInfo();
    }
}

std::vector<const Session*> Cinema::getSessionsByDay(std::string_view sessionDate) const {
    std::vector<const Session*> result;
    for (const auto& s : sessions) {
        if (s.getDate() == sessionDate) {
            result.push_back(&s);
        }
    }
    return result;
}

bool Cinema::buyTicketForSession(std::string_view title, std::string_view sessionDate,
    std::string_view sessionTime, bool isVip, int seatCount) {
    for (auto& s : sessions) {
        if (s.getMovieTitle() == title && s.getDate() == sessionDate && s.getStartTime() == sessionTime) {
            if (isVip) {
                return s.bookVipSeats(seatCount);
            }
            return s.bookRegularSeats(seatCount);
        }
    }
    return false;
}

int Cinema::getSessionCount() const {
    return static_cast<int>(sessions.size());
}

Session* Cinema::getSession(int index) {
    if (index >= 0 && index < static_cast<int>(sessions.size())) {
        return &sessions[index];
    }
    return nullptr;
}

const Session* Cinema::getSession(int index) const {
    if (index >= 0 && index < static_cast<int>(sessions.size())) {
        return &sessions[index];
    }
    return nullptr;
}