#include "Session.h"
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