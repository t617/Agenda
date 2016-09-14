#include "Storage.hpp"
#include <iostream>
#include <cstring>
#include <functional>
#include <fstream>
#include <list>
#include <vector>
#include "Path.hpp"

using namespace std;

shared_ptr<Storage> Storage::m_instance= NULL;

Storage::Storage() {
	m_dirty= false;
	readFromFile();
}

//  Storage::Storage(const Storage & t_another) = delete;

//  void Storage::operator=(const Storage & t_another) = delete;

bool Storage::readFromFile(void) {
	ifstream in, in1;
	string str;
	in.open(Path::userPath);
	if (!in.is_open()) return false;
	// getline(in, str);
	while (getline(in, str)) {
		string s[4];
		int j= 1;
		for (int i=0; i< 4; i++) {
			for (j; j< str.size()&& str[j]!= '\"'; j++) {
				s[i]+= str[j];
			}
			j+= 3;
		}
		m_userList.push_back(User(s[0], s[1], s[2], s[3]));
	}
	in.close();
	in1.open(Path::meetingPath);
	if (!in1.is_open()) return false;
	string str1;
	// getline(in1, str1);
	while (getline(in1, str1)) {
		std::string ss[5];
		int j= 1;
		for (int i= 0; i< 5; i++) {
			for (i; j< str1.size()&& str1[j]!= '\"'; j++) ss[i]+= str1[j];
			j+= 3;
		}
		vector<string> sv;
		string sss;
		for (int k= 0; k< ss[1].size(); k++) {
			if (ss[1][k]== '&') {
				sv.push_back(sss);
				sss.clear();
			} else {
				sss+= ss[1][k];
			}
		}
		sv.push_back(sss);
		Date d= Date::stringToDate(ss[2]);
		Date dd= Date::stringToDate(ss[3]);
		m_meetingList.push_back(Meeting(ss[0], sv, d, dd, ss[4]));
	}
	in1.close();
	return true;
}

bool Storage::writeToFile(void) {
	ofstream out;
	string s, s1;
	out.open(Path::userPath);
	if (!out.is_open()) return false;
	for (auto it= m_userList.begin(); it!= m_userList.end(); it++) {
		out<< "\""<< (*it).getName()<< "\",\""<< (*it).getPassword()<< "\",\""<< 
		(*it).getEmail()<< "\",\""<< (*it).getPhone()<< "\""<< std::endl;
	}
	out.close();
	out.open(Path::meetingPath);
	//  if (!out1.is_open()) return false;
	for (auto it1= m_meetingList.begin(); it1!= m_meetingList.end(); it1++) {
		out<< "\""<< it1->getSponsor()<< "\",\""<< it1->getParticipator()[0];
		for (int i= 1; i< it1->getParticipator().size(); i++) {
			out<< "&"+ it1->getParticipator()[i];
		}
		out << "\",\"" <<  Date::dateToString((*it1).getStartDate())
		 << "\",\""<< Date::dateToString((*it1).getEndDate())<<"\",\""<< (*it1).getTitle()<< "\""<< std::endl;
	}
	out.close();
	return true;
}

std::shared_ptr<Storage> Storage::getInstance(void) {
	if (m_instance== NULL) {
		m_instance= shared_ptr<Storage> (new Storage);
	}
	return  m_instance;
}

Storage::~Storage() {
	writeToFile();
	m_instance= NULL;
}

void Storage::createUser(const User & t_user) {
	m_userList.push_back(t_user);
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const {
	list<User> temp;
	for (auto it= m_userList.begin(); it!= m_userList.end(); it++) {
		if (filter(*it)) {
			temp.push_back(*it);
		}
	}
	return temp;
}

int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher) {
	int s= 0;
	for (auto it= m_userList.begin(); it!= m_userList.end(); it++) {
		if (filter(*it)) {
			switcher(*it);
			s++;
		}
	}
	return s;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
	std::list<User>::iterator it;
	int s= 0;
	for (it= m_userList.begin(); it!= m_userList.end();) {
		if (filter(*it)) {
			m_userList.erase(it++);
			s++;
		} else {
			it++;
		}
	}
	return s;
}

void Storage::createMeeting(const Meeting & t_meeting) {
	m_meetingList.push_back(t_meeting);
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
	std::list<Meeting> temp;
	for (auto it= m_meetingList.begin(); it!= m_meetingList.end(); it++) {
		if (filter(*it)) {
			temp.push_back(*it);
		}
	}
	return temp;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
	std::list<Meeting>::iterator it;
	int s= 0;
	for (it= m_meetingList.begin(); it!= m_meetingList.end(); it++) {
		if (filter(*it)) {
			switcher(*it);
			s++;
		}
	}
	return s;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
	std::list<Meeting>::iterator it;
	int s= 0;
	for (it= m_meetingList.begin(); it!= m_meetingList.end();) {
		if (filter(*it)) {
			m_meetingList.erase(it++);
			s++;
		} else {
			it++;
		}
	}
	return s;
}


bool Storage::sync(void) {
	return writeToFile();
}
