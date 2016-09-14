#include "Storage.hpp"
#include <list>
#include <functional>
#include <string>
#include "AgendaService.hpp"
using namespace std;
AgendaService::AgendaService() {
    startAgenda();
}

AgendaService::~AgendaService() { m_storage= NULL; }

bool AgendaService::userLogIn(const string userName, const string password) {
    if (!m_storage-> queryUser([userName, password](const User & user) {
        return user.getName()== userName&& user.getPassword()== password;
    }).empty()) return true;
    return false; 
}

bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone) {
    if (m_storage-> queryUser([userName](const User & user) {
            return user.getName()== userName;
        }).empty()){
        User temp(userName, password, email, phone);
        m_storage->createUser(temp);
        return true;
    }
    return false;
}

bool AgendaService::deleteUser(const std::string userName, const std::string password) {
    if (m_storage->deleteUser([userName, password](const User& temp) {
        return (temp.getName()== userName&& temp.getPassword()== password);
    })) {
        AgendaService::deleteAllMeetings(userName);
        return true;
    }
    return false;
}

std::list<User> AgendaService::listAllUsers(void) const {
    return m_storage->queryUser([](const User& temp) {
        return true;
    });
}

bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> participator) {
    Date d= Date::stringToDate(startDate);
    Date dd= Date::stringToDate(endDate);

    /*for (auto it= participator.begin(); it!= participator.end(); it++) {
        if (*it== userName) return false;
    }

    if (m_storage->queryUser([userName](const User& temp) {
        return temp.getName()== userName;
    }).empty()) return false;


    for (auto it= participator.begin(); it!= participator.end(); it++) {
        if (m_storage->queryUser([it](const User& temp) {
            return temp.getName()== *it;
        }).empty()) return false;
    }


    if (!(meetingQuery(userName, title).empty())) return false;

    for (auto it= participator.begin(); it!= participator.end(); it++) {
        if (!meetingQuery(*it, title).empty())
            return false;
    }
    // judge Date
    if (!Date::isValid(dd)|| !Date::isValid(d)|| d>= dd) return false;

    list<Meeting> temp= listAllMeetings(userName);
    for (auto it= temp.begin(); it!= temp.end(); it++) {
        if (!(it->getStartDate()>= dd|| d>= it->getEndDate())) return false;
    }
    for (auto it= participator.begin(); it!= participator.end(); it++) {
        list<Meeting> temp= listAllMeetings(*it);
        for (auto it= temp.begin(); it!= temp.end(); it++) {
            if (!(it->getStartDate()>= dd|| it->getEndDate()<= d)) {
            return false;
        }
        }
    }*/

    Meeting m(userName, participator, d, dd, title);
    m_storage->createMeeting(m);
    return true;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const {
    return m_storage->queryMeeting([userName, title](const Meeting& temp) {
        if (temp.getTitle()== title&&temp.getSponsor()== userName) return true;
        for (auto it= temp.getParticipator().begin(); it!= temp.getParticipator().end(); it++) {
            if (*it== userName) return true;
        }
    return false;
    });
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const {
    Date d= Date::stringToDate(startDate);
    Date dd= Date::stringToDate(endDate);
    return m_storage->queryMeeting([userName, d, dd](const Meeting& temp) {
        if (temp.getSponsor()== userName||temp.isParticipator(userName))
        return (!(temp.getStartDate()> dd|| temp.getEndDate()< d));
    });
}

std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const {
    list<Meeting> temp = listAllSponsorMeetings(userName);
    list<Meeting> temp1= listAllParticipateMeetings(userName);
    for (auto it= temp1.begin(); it!= temp1.end(); it++) temp.push_back(*it);
    return temp;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const {
    return m_storage->queryMeeting([userName](const Meeting& temp) {
        return temp.getSponsor()== userName;
    });
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string userName) const {
    return m_storage->queryMeeting([userName](const Meeting& temp) {
        return temp.isParticipator(userName);
    });
}

bool AgendaService::deleteMeeting(const std::string userName, const std::string title) {
    return (m_storage->deleteMeeting([userName, title](const Meeting& temp) {
        return title== temp.getTitle()&&temp.getSponsor()== userName;
    }));
}

bool AgendaService::deleteAllMeetings(const std::string userName) {
    return (m_storage->deleteMeeting([userName](const Meeting& temp) {
        return (temp.getSponsor()== userName||temp.isParticipator(userName));
    }));
}

void AgendaService::startAgenda(void) {
    m_storage = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
    m_storage->sync();
}
