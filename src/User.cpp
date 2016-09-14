#include "User.hpp"
#include <iostream>
using namespace std;

User::User(std::string t_userName, std::string t_userPassword,
       std::string t_userEmail, std::string t_userPhone) {
       setName(t_userName);
       setPassword(t_userPassword);
       setEmail(t_userEmail);
       setPhone(t_userPhone);
       }

User::User(const User &t_user) {
	setName(t_user.getName());
	setPassword(t_user.getPassword());
	setEmail(t_user.getEmail());
	setPhone(t_user.getPhone());
}

std::string User::getName() const {
	return m_name;
}

void User::setName(std::string t_name) {
	m_name= t_name;
}

std::string User::getPassword() const {
	return m_password;
}

void User::setPassword(std::string t_password) {
	m_password= t_password;
}

std::string User::getEmail() const {
	return m_email;
}

void User::setEmail(std::string t_email) {
	m_email= t_email;
}

std::string User::getPhone() const {
	return m_phone;
}

void User::setPhone(std::string t_phone) {
	m_phone= t_phone;
}
