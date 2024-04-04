#include "date.h"
#include "person.h"
#include "contact.h"
#include <iostream>

Person::Person(){
    set_person();
}

Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
    //delete next;
    //delete prev;
}

Person::Person(string f_name, string l_name, string b_date, string email, string phone){
    // TODO: Complete this method!
    // phone and email strings are in full version
    this->f_name = f_name;
    this->l_name = l_name;
    this->birthdate = new Date(b_date);
    this->email = new Email("email", email);
    this->phone = new Phone("phone", phone);
}

Person::Person(string filename){
    set_person(filename);
}

void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    
    string temp;
    string type;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    std::getline(std::cin,type);

    cout << "Email address: ";
    std::getline(std::cin,temp);
    email = new Email(type, temp);

    cout << "Type of phone number: ";
    std::getline(std::cin,type);

    cout << "Phone number: ";
    std::getline(std::cin,temp);
    phone = new Phone(type, temp);

}

void Person::set_person(string filename){
     fstream person_file;
     person_file.open(filename.c_str());
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!
    ifstream file(filename);

    if(file.is_open()){
        string temp;
        string type;
        getline(file, f_name);
        getline(file, l_name);

        getline(file, temp);
        birthdate = new Date(temp); 

        file >> type; 
        file >> temp;
        phone = new Phone(type, temp);

        file >> type;
        file >> temp;
        email = new Email(type, temp);
    
        file.close();
    }
}

bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    return (f_name == rhs.f_name) && (l_name == rhs.l_name) && (birthdate->get_date() == rhs.birthdate->get_date());
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    return !(*this==rhs);
}

void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date();
    phone->print();
    email->print();
}
