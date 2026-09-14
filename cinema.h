#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <vector>
#include <string_view>

class Session {
private:
    std::string movieTitle;
    std::string genre;
    std::string startTime;
    int totalSeats;
    int soldSeats = 0; 

public:
    Session(std::string_view title, std::string_view movieGenre, std::string_view time, int seats);

    std::string getMovieTitle() const;
    std::string getGenre() const;
    std::string getStartTime() const;
    int getTotalSeats() const;
    int getSoldSeats() const;
    int getAvailableSeats() const;

    void setStartTime(std::string_view newTime);
    bool bookSeats(int count);
    void printInfo() const;
};

class Cinema {
private:
    std::string name;
    std::vector<Session> sessions;

public:
    explicit Cinema(std::string_view cinemaName);
    void addSession(const Session& session);
    void showSchedule() const;
    void buyTicket(std::string_view movieTitle, int seatCount);
    int getSessionCount() const;
    const Session* getSession(int index) const;
};

#endif 