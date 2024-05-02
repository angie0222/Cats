#include "date.h"

Date::Date(){

}
Date::~Date(){

}
Date::Date(string b_date){
    this->birthdate = b_date;
}
string Date::get_date(){
    return birthdate;
}
void Date::set_date(string bd){
    this->birthdate = bd;
}
void Date::print_date(){
    cout << this->birthdate << endl;
}