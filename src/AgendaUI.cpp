#include <iostream>
#include <string>
#include <iomanip>
#include "AgendaUI.hpp"
using namespace std;


AgendaUI::AgendaUI() {
	startAgenda();
}

void AgendaUI::OperationLoop(void) {
	if (m_userName.empty()||m_userPassword.empty()) return;
	cout<< endl
	    << "----------------------Agenda------------------------"<< endl<< endl
	    << "Action : "<< endl
	    << "o    - log out Agenda"<< endl
	    << "dc   - Delete Agenda Account"<< endl
	    << "lu   - list all Agenda user"<< endl
	    << "cm   - create a meeting"<< endl
	    << "la   - list all meetings"<< endl
	    << "las  - list all sponsor meetings"<< endl
	    << "lap  - list all listAllParticipate meetings"<< endl
	    << "qm   - query meeting by title"<< endl
	    << "qt   - query meeting by time interval"<< endl
	    << "dm   - delete meeting by title"<< endl
	    << "da   - delete all meetings"<< endl
	    << "----------------------------------------------------"<< endl<< endl;
	cout<< "Agenda@"<< m_userName<< " : #";
	if (!executeOperation("#")) {
		cout<< "[error] your order is invalid!"<< endl;
		OperationLoop();
	}
}

void AgendaUI::startAgenda(void) {
	m_userName.clear();
	m_userPassword.clear();
	cout<< endl
	    << "---------------------------Agenda----------------------------"<< endl<< endl
	    << "Action : "<< endl
	    << "l   - log in an Agenda by user name and password"<< endl
	    << "r   - register an Agenda Account"<< endl
	    << "q   - quit Agenda"<< endl
	    << "-------------------------------------------------------------"<< endl<< endl
	    << endl
	    << "Agenda : ~$ ";
	if (!executeOperation("~$")) {
		cout<< "[error] Your input is invalid"<< endl;
		startAgenda();
	}
}


std::string AgendaUI::getOperation() {
	string str;
	cin>> str;
	return str;
}


bool AgendaUI::executeOperation(std::string t_operation) {
	if (t_operation== "~$") {
		t_operation= getOperation();
		if (t_operation== "l") {
			userLogIn();
			return true;
		} else if (t_operation== "r") {
			userRegister();
			return true;
		} else if (t_operation== "q") {
			quitAgenda();
			return true;
		} else {
			return false;
		}
	}
	if (t_operation== "#") {
		t_operation= getOperation();
		if (t_operation== "o") {
			userLogOut();
			return true;
		} else if (t_operation== "dc") {
			deleteUser();
			return true;
		} else if (t_operation== "lu") {
			listAllUsers();
			return true;
		} else if (t_operation== "cm") {
			createMeeting();
		} else if (t_operation== "la") {
			listAllMeetings();
		} else if (t_operation== "las") {
			listAllSponsorMeetings();
		} else if (t_operation== "lap") {
			listAllParticipateMeetings();
		} else if (t_operation== "qm") {
			queryMeetingByTitle();
		} else if (t_operation== "qt") {
			queryMeetingByTimeInterval();
		} else if (t_operation== "dm") {
			deleteMeetingByTitle();
		} else if (t_operation== "da") {
			deleteAllMeetings();
		}
	}
	if (t_operation== "~#") {
		t_operation= getOperation();
		if (t_operation== "return") {
			OperationLoop();
			return true;
		} else {
			cout<< endl;
			cout<< "return     --return to the menu"<< endl
			    << "[return]: ~# "
			    << "your order is invalid, please input a new one";
			    executeOperation("~#");
		}
	}
	return false;
}


void AgendaUI::userLogIn(void) {
	cout<< endl
	    << "[log in] [user name] [password]"<< endl
	    << "[log in] ";
	cin>> m_userName>> m_userPassword;
	if (m_agendaService.userLogIn(m_userName, m_userPassword)) {
		cout<< "[log in] succeed!"<< endl;
		OperationLoop();
	} else {
		cout<< "[error] log in fail!"<< endl;
		startAgenda(); 
	}
}


void AgendaUI::userRegister(void) {
	cout<< endl<< "[register] [user name] [password] [email] [phone]"<< endl<< "[register] ";
	string name, password, email, phone;
	cin>> name>> password>> email>> phone;
	if (m_agendaService.userRegister(name, password, email, phone)) {
		cout<< "[register] succeed!"<< endl;
		m_userName= name;
		m_userPassword= password;
		OperationLoop();
	} else {
		cout<< "[error] register fail!"<< endl;
	}
}

 
void AgendaUI::quitAgenda(void) {
	cout<< "-------------------------------------------------"<< endl<< endl
	    << "Thank you to use this meeting(appointment) system!"<< endl
	    << "We are desire to meet you again"<< endl
	    << "------------             -------------"<< endl
	    << "------------             -------------"<< endl
	    << endl<< endl
	    << "            --          --            "<< endl
	    << "             --        --             "<< endl
	    << "              --      --              "<< endl
	    << "                ------                "<< endl
	    << "-------------------------------------------------"<< endl;
	    m_agendaService.quitAgenda();
}

 
void AgendaUI::userLogOut(void) {
	m_userName.clear();
	m_userPassword.clear();
	startAgenda();
}


void AgendaUI::deleteUser(void) {
	cout<< endl;
	m_agendaService.deleteUser(m_userName, m_userPassword);
	cout<< "[delete agenda account] succeed!"<< endl;
	m_userName.clear();
	m_userPassword.clear();
	startAgenda();
}


void AgendaUI::listAllUsers(void) {
	cout<< endl;
	cout<< "[list all users]"<< endl<< endl
	    << left<< setw(10)<< "name"<< setw(20)<< "email"<< setw(20)<< "phone"<< endl<< endl;
	list<User> users = m_agendaService.listAllUsers();
	for (auto it= users.begin(); it!= users.end(); it++) {
		cout<< left<< setw(10)<< it->getName()<< setw(20)<< it->getEmail()<< setw(20)<<
		it->getPhone()<< endl;
	}
	cout<< "return    --return to the menu"<< endl
	    << "[return]: ~#";
	executeOperation("~#");
}


void AgendaUI::createMeeting(void) {
	int num;
	vector<string> participator;
	string title, stime, etime, str;
	cout<< endl<< "[creat meeting] [the number of participators]"<< endl<< "[creat meeting] ";
	cin>> num;
	for (int i= 1; i<= num; i++) {
		cout<< endl<< "[creat meeting] [please enter the participator "<< i<< " ]"<< endl<< "[creat meeting] ";
		cin>> str;
		participator.push_back(str);

	}
	cout<< endl<< "[creat meeting] [title] [start time(yyyy-mm-dd/hh:mm)]  [end time(yyyy-mm-dd/hh:mm)]"
	    << endl<< "[creat meeting] ";
	
	
	cin>> title>> stime>> etime;
	if (m_agendaService.createMeeting(m_userName, title, stime, etime, participator))
		cout<< endl<< "[creat meeting] : succeed!"<< endl;
	else 
		cout << endl<< "error"<< endl;
	cout<< "[return]   --return to the menu"<< endl<< "[return]: ~#";
	executeOperation("~#");
}


void AgendaUI::listAllMeetings(void) {
	cout<< endl<< "[list all meetings]"<< endl
	    << left<< setw(20)<< "title"<< setw(20)<< "sponsor"
	    << setw(20)<< "participator"<< setw(20)<< "start time"
	    << setw(20)<< "end time"<< endl;
	list<Meeting> meetings = m_agendaService.listAllMeetings(m_userName);
	printMeetings(meetings);
	cout<< "[return]   --return to the menu"<< endl<< "[return]: ~#";
	executeOperation("~#");
}


void AgendaUI::listAllSponsorMeetings(void) {
	cout<< endl<< "[list all sponsor meetings]"<< endl
	    << left<< setw(20)<< "title"<< setw(20)<< "sponsor"
	    << setw(20)<< "participator"<< setw(20)<< "start time"
	    << setw(20)<< "end time"<< endl;
	list<Meeting> meetings= m_agendaService.listAllSponsorMeetings(m_userName);
	printMeetings(meetings);
	cout<< "[return]   --return to the menu"<< endl<< "[return]: ~#";
	executeOperation("~#");
}


void AgendaUI::listAllParticipateMeetings(void) {
	cout<< endl<< "[list all participator meetings]"<< endl
	    << left<< setw(20)<< "title"<< setw(20)<< "sponsor"
	    << setw(20)<< "participator"<< setw(20)<< "start time"
	    << setw(20)<< "end time"<< endl;
	list<Meeting>meetings = m_agendaService.listAllParticipateMeetings(m_userName);
	printMeetings(meetings);
	cout<< "[return]   --return to the menu"<< endl<< "[return]: ~#";
	executeOperation("~#");
}

 
void AgendaUI::queryMeetingByTitle(void) {
	cout<< endl<< "[query meeting] [title]"<< endl<< "[query meeting]";
	string title;
	cin>> title;
	cout<< endl;
	list<Meeting> meetings = m_agendaService.meetingQuery(m_userName, title);
	cout<< left<< setw(20)<< "title"<< setw(20)<< "sponsor"
	    << setw(20)<< "participator"<< setw(20)<< "start time"
	    << setw(20)<< "end time"<< endl;
	printMeetings(meetings);
	cout<< "[return]   --return to the menu"<< endl<< "[return]: ~#";
	executeOperation("~#");
}

  
void AgendaUI::queryMeetingByTimeInterval(void) {
	cout<< endl<< "[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"
	<< endl<< "[query meeting]";
	string stime, etime;
	cin>> stime>> etime;
	cout<< endl;
	list<Meeting>meetings = m_agendaService.meetingQuery(m_userName, stime, etime);
	cout<< left<< setw(20)<< "title"<< setw(20)<< "sponsor"
	    << setw(20)<< "participator"<< setw(20)<< "start time"
	    << setw(20)<< "end time"<< endl;
	printMeetings(meetings);
	cout<< "[return]   --return to the menu"<< endl<< "[return]: ~#";
	executeOperation("~#");
}

   
void AgendaUI::deleteMeetingByTitle(void) {
	cout<< endl<< "[delete meeting] [title]"<< endl<< "[delete meeting]";
	string title;
	cin>> title;
	cout<< endl;
	if (m_agendaService.deleteMeeting(m_userName, title))
		cout<< "[delete meeting by title] succeed!"<< endl;
	else
		cout<< "[error] delete meeting fail!"<< endl;
	cout<< "[return]   --return to the menu"<< endl<< "[return]: ~#";
	executeOperation("~#");
}

  
void AgendaUI::deleteAllMeetings(void) {
	cout<< endl;
	if (m_agendaService.deleteAllMeetings(m_userName))
	cout<< "[delete all meetings] succeed!"<< endl;
    cout<< "[return]   --return to the menu"<< endl<< "[return]: ~#";
	executeOperation("~#");
}


void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
	for (auto it= t_meetings.begin(); it!= t_meetings.end(); it++) {
		cout<< left<< setw(20)<< it->getTitle()<< setw(20)<< it->getSponsor()
		<< Date::dateToString(it->getStartDate())<< setw(20)<< Date::dateToString(it->getEndDate())<< setw(20)
		<< it->getParticipator()[0];
		for (auto it1= it->getParticipator().begin()+ 1; it1!= it->getParticipator().end(); it1++) {
			cout<< ","<< *it1;
		}
	}
}
