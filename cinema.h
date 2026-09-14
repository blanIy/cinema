#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <vector>
#include <string_view>

class Session {
private:
    std::string movieTitle;
    std::string genre;
    std::string date;    
    std::string startTime; 

    int totalRegularSeats = 0;
    int soldRegularSeats = 0;
    int totalVipSeats = 0;
    int soldVipSeats = 0;

public:
    Session(std::string_view title, std::string_view movieGenre, std::string_view sessionDate,
        std::string_view time, int regularSeats, int vipSeats);

    std::string getMovieTitle() const;
    std::string getGenre() const;
    std::string getStartTime() const;
    std::string getDate() const;

    int getAvailableRegularSeats() const;
    int getAvailableVipSeats() const;
    int getTotalRegularSeats() const;
    int getTotalVipSeats() const;

    bool bookRegularSeats(int count);
    bool bookVipSeats(int count);

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
    std::vector<const Session*> getSessionsByDay(std::string_view sessionDate) const;
    bool buyTicketForSession(std::string_view title, std::string_view sessionDate,
        std::string_view sessionTime, bool isVip, int seatCount);
};

#endif 