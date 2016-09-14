#include "Date.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

Date::Date() {
	setYear(0);
	setMonth(0);
	setDay(0);
	setHour(0);
	setMinute(0);
}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
	setYear(t_year);
	setMonth(t_month);
	setDay(t_day);
	setHour(t_hour);
	setMinute(t_minute);
}

Date::Date(std::string dateString) {
	*this= stringToDate(dateString);
}

int Date::getYear(void) const {
	return m_year;
}

void Date::setYear(const int t_year) {
	m_year= t_year;
}

int Date::getMonth(void) const {
	return m_month;
}

  
void Date::setMonth(const int t_month) {
	m_month= t_month;
}

  
int Date::getDay(void) const {
	return m_day;
}

void Date::setDay(const int t_day) {
	m_day= t_day;
}

int Date::getHour(void) const {
	return m_hour;
}

void Date::setHour(const int t_hour) {
	m_hour= t_hour;
}

int Date::getMinute(void) const {
	return m_minute;
}

void Date::setMinute(const int t_minute) {
	m_minute= t_minute;
}

inline bool dyear(int y) {
	if (y>= 1000&&y<= 9999) {
	return true;
	}
	return false;
}

inline bool dmonth(int m) {
	if (m< 1||m> 12) {
	return false;
	}
	return true;
}

inline bool dhour(int h) {
	if (h< 0||h> 23) {
	return false;
	}
	return true;
}

inline bool dminute(int m) {
	if (m< 0||m> 59) {
	return false;
	}
	return true;
}

bool Date::isValid(const Date t_date) {
	if (!dyear(t_date.getYear())||!dmonth(t_date.getMonth())||!dhour(t_date.getHour())||!dminute(t_date.getMinute()))  // judge year,month,hour,minute
	return false;
	if (t_date.getMonth()== 1||t_date.getMonth()== 3||t_date.getMonth()== 5||t_date.getMonth()== 7|| t_date.getMonth()== 8|| t_date.getMonth()== 10|| t_date.getMonth()== 12) {
	if (t_date.getDay()< 1|| t_date.getDay()> 31) {
	return false;
	}
	}
	if (t_date.getMonth()== 4||t_date.getMonth()== 6||t_date.getMonth()== 9||t_date.getMonth()== 11) {
	if (t_date.getDay()< 1|| t_date.getDay()> 30) {
	return false;
	}
	}
	if (t_date.getYear()% 400== 0|| t_date.getYear()% 4== 0&& t_date.getYear()% 100!= 0) {
		if (t_date.getMonth()== 2&&(t_date.getDay()< 1|| t_date.getDay()> 29)) {
			return false;
		}
	} else {
		if (t_date.getMonth()== 2&&(t_date.getDay()< 1|| t_date.getDay()> 28)) {
			return false;
		}
	}
	return true;
}

Date Date::stringToDate(const std::string t_dateString) {
	Date temp;
	for (int i= 0; i< 16; i++) {  // judge whether the string is vallid.
		if (((i== 4||i== 7)&& t_dateString[i]!= '-')||(i== 10&& t_dateString[i]!= '/')|| (i== 13&& t_dateString[i]!= ':')) return temp;
		if ((i!= 4&& i!= 7&& i!= 10&& i!= 13)&&(t_dateString[i]< '0'||t_dateString[i]> '9')) return temp;
	}
	temp.setYear((t_dateString[0]- 48)* 1000+ (t_dateString[1]- 48)* 100+ (t_dateString[2]- 48)* 10+ t_dateString[3]- 48);
	temp.setMonth((t_dateString[5]- 48)* 10+ t_dateString[6]- 48);
	temp.setDay((t_dateString[8]- 48)* 10+ t_dateString[9]- 48);
	temp.setHour((t_dateString[11]- 48)* 10+ t_dateString[12]- 48);
	temp.setMinute((t_dateString[14]- 48)* 10+ t_dateString[15]- 48);
	return temp;
}

std::string Date::dateToString(Date t_date) {
	if (isValid(t_date)) {
		char s[17];
	    s[0]= t_date.getYear()/ 1000+ 48;
	    s[1]= (t_date.getYear()/ 100)% 10+ 48;
	    s[2]= (t_date.getYear()% 100)/ 10+ 48;
	    s[3]= t_date.getYear()%10 + 48;
	    s[4]= '-';
	    s[5]= t_date.getMonth()/ 10+ 48;
	    s[6]= t_date.getMonth()% 10+ 48;
	    s[7]= '-';
	    s[8]= t_date.getDay()/ 10+ 48;
	    s[9]= t_date.getDay()% 10+ 48;
	    s[10]= '/';
	    s[11]= t_date.getHour()/ 10+ 48;
	    s[12]= t_date.getHour()% 10 +48;
	    s[13]= ':';
	    s[14]= t_date.getMinute()/ 10+ 48;
	    s[15]= t_date.getMinute()% 10+ 48;
	    s[16]= '\0';
	    string str(s);
	    return str;
	} else {
		return "0000-00-00/00:00";
	}
	
}

Date& Date::operator=(const Date &t_date) {
	setYear(t_date.getYear());
	setMonth(t_date.getMonth());
	setDay(t_date.getDay());
	setHour(t_date.getHour());
	setMinute(t_date.getMinute());
	return *this;
}

bool Date::operator==(const Date &t_date) const {
	return (getYear()== t_date.getYear()&& getMonth()== t_date.getMonth()&& getDay()== t_date.getDay()&&
		getHour()== t_date.getHour()&& getMinute()== t_date.getMinute());
}

bool Date::operator>(const Date &t_date) const {
	if (getYear()> t_date.getYear()) return true;
	if (getYear()< t_date.getYear()) return false;
	if (getYear()== t_date.getYear()) {
		if (getMonth()> t_date.getMonth()) return true;
		if (getMonth()< t_date.getMonth()) return false;
		if (getMonth()== t_date.getMonth()) {
			if (getDay()> t_date.getDay()) return true;
			if (getDay()< t_date.getDay()) return false;
			if (getDay()== t_date.getDay()) {
				if (getHour()> t_date.getHour()) return true;
				if (getHour()< t_date.getHour()) return false;
				if (getHour()== t_date.getHour()) {
					if (getMinute()> t_date.getMinute()) return true;
					if (getMinute()< t_date.getMinute()) return false;
					if (getMinute()== t_date.getMinute()) return false;
				}
			}
		}
	}
}

bool Date::operator<(const Date &t_date) const {
	return !(*this== t_date|| *this> t_date);
}

bool Date::operator>=(const Date &t_date) const {
	return (*this> t_date|| *this== t_date);
}

bool Date::operator<=(const Date &t_date) const {
	return !(*this> t_date);
}

