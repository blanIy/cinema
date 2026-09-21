#pragma once
#include "Session.h"
#include <string>
#include <vector>
#include <string_view>

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

    int getSessionCount() const;

    Session* getSession(int index);
    const Session* getSession(int index) const;
};
