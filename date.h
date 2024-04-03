
#ifndef DATE_H
#define DATE_H

#include "person.h"
#include "contact.h"
#include "fstream"
class Date{
    friend class Network;

private:
	string f_name;
	string l_name;
	Date *birthdate;
    // the following to attributes are used in the linked list.
    Person* next;
    Person* prev;

public: 
    Date();
    ~Date();
    Date(string b_date);
	string print_date();
};


#endif