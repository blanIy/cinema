#include "Cinema.h"
#include <iostream>

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