#include "date.h"
#include "person.h"
#include "contact.h"
#include "misc.h"
#include <map>
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
void Person::makeFriend(Person* newFriend){
    myfriends.push_back(newFriend);
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
	cout << l_name << ", " << f_name << endl;
	birthdate->print_date();
    phone->print();
    email->print();

    for(int i = 0; i < myfriends.size(); i++){
        cout << codeName(myfriends[i]->f_name, myfriends[i]->l_name) << " (" << myfriends[i]->f_name << " " << myfriends[i]->l_name << ")" << endl;
    }
}
void Person::pprint_friends(){
    cout << this->f_name << ", " << this->l_name << endl;
    cout << "-----------------------------" << endl;

    vector<Person*>::iterator it = myfriends.begin();
    vector<string> friendIds;
    map<string, Person*> mapFriend;
    for(; it != myfriends.end(); ++it){
        friendIds.push_back(codeName((*it)->f_name, (*it)->l_name));
        mapFriend.insert(pair<string, Person*>(codeName((*it)->f_name, (*it)->l_name), *it));
    }
    sort(friendIds.begin(), friendIds.end());

    vector<string>::iterator it1 = friendIds.begin();
    for(;it1 != friendIds.end(); ++it1){
        map<string, Person*>::iterator it2 = mapFriend.find(*it1);
        cout << (it2)->second->f_name << ", " << (it2)->second->l_name << endl;
    }

}
