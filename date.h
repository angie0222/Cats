#ifndef DATE_H
#define DATE_H

#include "contact.h"
#include "fstream"
class Date{

private:
	string birthdate;

public: 
    Date();
    ~Date();
    Date(string b_date);
    string get_date();
    void set_date(string bd);
	void print_date();
};


#endif