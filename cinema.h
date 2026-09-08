#ifndef CINEMA_H
#define CINEMA_H

#include <string>

// =================================================================
// Объявление класса Session (Сеанс)
// =================================================================
class Session {
private:
    std::string movieTitle;
    std::string genre;
    std::string startTime;
    int totalSeats;
    int soldSeats;

public:
    Session(std::string title, std::string movieGenre, std::string time, int seats);

    std::string getMovieTitle() const;
    std::string getGenre() const;
    std::string getStartTime() const;
    int getTotalSeats() const;
    int getSoldSeats() const;
    int getAvailableSeats() const;

    void setStartTime(const std::string& newTime);
    bool bookSeats(int count);
    void printInfo() const;
};

// =================================================================
// Объявление класса Cinema (Кинотеатр)
// =================================================================
class Cinema {
private:
    std::string name;
    Session** sessions;
    int count;
    int capacity;

    void resize();

public:
    Cinema(std::string cinemaName);
    ~Cinema();
    Cinema(const Cinema& other);
    Cinema& operator=(const Cinema& other);

    void addSession(const Session& session);
    void showSchedule() const;
    void buyTicket(const std::string& movieTitle, int seatCount);

    // Новые геттеры для динамического построения меню покупки
    int getSessionCount() const;
    Session* getSession(int index) const;
};

#endif // CINEMA_H