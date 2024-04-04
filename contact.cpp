#include <iostream>
#include <string>
#include "contact.h"
#include <string>
#include <iostream>
// TODO: Add needed libraries! 

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this->email_addr = email_addr;
    Contact::type = type;
}

void Email::set_contact() {
    cout << "Enter the type of email address: ";
    cin >> this->type;
    cout << "Enter email address: ";
    cin >> email_addr;
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "(" + type + ") " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact("full") << endl;
}

Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    this->type = type;
    //cout << "This is the type: " << type << endl;
    //cout << "This is the phone number: " << num << endl;
    // Remove any dashes from the number and store it
    string::size_type pos;
    while ((pos = num.find('-')) != string::npos) {
        num.erase(pos, 1);
    }
    this->phone_num = stoull(num);

}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
    cin >> Contact::type;
	cout << "Enter the phone number: ";
    cin >> phone_num;
}


string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    if (style=="full")
	    return "(" + type + ") " + to_string(phone_num);
    else 
        return to_string(phone_num);
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact("full") << endl;
}

