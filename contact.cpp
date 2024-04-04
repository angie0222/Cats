#include <iostream>
#include <string>
#include "contact.h"

using namespace std;

Email::Email(string type, string email_addr) {
    this->type = type;
    this->email_addr = email_addr;
}

void Email::set_contact() {
    cout << "Enter the type of email address: ";
    getline(cin, type);
    cout << "Enter email address: ";
    getline(cin, email_addr);
}

string Email::get_contact(string style) {
    if (style == "full")
        return "(" + type + ") " + email_addr;
    else
        return email_addr;
}

void Email::print() {
    cout << "Email " << get_contact() << endl;
}

Phone::Phone(string type, string num) {
    this->type = type;
    // Remove any dashes from the number and store it
    string::size_type pos;
    while ((pos = num.find('-')) != string::npos) {
        num.erase(pos, 1);
    }
    this->phone_num= num;
}

void Phone::set_contact() {
    cout << "Enter the type of phone number: ";
    getline(cin, type);
    cout << "Enter the phone number: ";
    getline(cin, phone_num);
    // Remove any dashes entered by user
    string::size_type pos;
    while ((pos = phone_num.find('-')) != string::npos) {
        phone_num.erase(pos, 1);
    }
}

string Phone::get_contact(string style) {
    // Format the phone number with dashes
    string formatted_number = phone_num;
    if (style == "full") {
        formatted_number.insert(3, "-");
        formatted_number.insert(7, "-");
        return "(" + type + ") " + formatted_number;
    } else {
        return formatted_number;
    }
}

void Phone::print() {
    cout << "Phone " << get_contact("full") << endl;
}


int main() {
    // Example usage of Email and Phone
    Email myEmail("Work", "angievas@usc.edu");
    myEmail.print();

    Phone myPhone("Mobile", "3239944786");
    myPhone.print();

    return 0;
}