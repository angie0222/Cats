
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <sstream>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}

Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);
}

Network::~Network(){ 
}

Person* Network::search(Person* searchEntry){

    Person* ptr = head;
    while(ptr != NULL) {
        if(*ptr == *searchEntry) // Assuming the == operator is overloaded for Person
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}


Person* Network::search(string fname, string lname){ //Natalia
    Person* ptr = head;
    while(ptr != NULL) {
        if((ptr->f_name == fname) && (ptr->l_name == lname)) // Assuming the == operator is overloaded for Person
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

void Network::loadDB(string filename){
    // TODO: Complete this method
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File " << filename << " cannot be opened!" << endl;
        return;
    }
    // Assuming a specific format for each line in the file representing a Person
    string line, f_name, l_name, b_date, email, phone;
    while(getline(file, line)){
        if(line == "--------------------" || line.empty()){
            continue;
        }
        f_name = line;
        getline(file, l_name);
        getline(file, b_date);
        getline(file, email);
        getline(file, phone);
        //istringstream iss(line);
        //string typeE = email.substr(1, email.find(')') - 1);
        email = email.substr(email.find(')') + 2);
        //string typeP = phone.substr(1, phone.find(')') - 1);
        phone = phone.substr(phone.find(')') + 2);
        Person* newPerson = new Person(f_name, l_name, b_date, email, phone);
        push_back(newPerson); // Or push_front, depending on desired list order
    }
    file.close();
}

void Network::saveDB(string filename){
    // TODO: Complete this method
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "File " << filename << " cannot be opened for writing!" << endl;
        return;
    }
    Person* ptr = head;
    while(ptr != NULL) {
        file << ptr->l_name << ", " << ptr->f_name << endl;
        file << ptr->birthdate->get_date() << endl;
        file << ptr->phone->DBcontact() << endl;
        file << ptr->email->DBcontact() << endl;
        file << "-----------------------------" << endl;
        ptr = ptr->next;
    }
    file.close();
}

void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Personattributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}

void Network::push_front(Person* newEntry){
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){ //Natalia
    // Adds a new Person (newEntry) to the back of LL
    newEntry -> next = NULL;
    newEntry -> prev = tail; 
    
    if (tail != NULL){
        tail -> next = newEntry;
    }
    else{
        head = newEntry;
    }
    tail = newEntry;
    count++;
}


bool Network::remove(string fname, string lname){
    // TODO: Complete this method
    Person* ptr = head;
    while(ptr != NULL) {
        if(ptr->f_name == fname && ptr->l_name == lname) {
            if(ptr->prev) ptr->prev->next = ptr->next;
            else head = ptr->next;
            if(ptr->next) ptr->next->prev = ptr->prev;
            else tail = ptr->prev;
            delete ptr;
            count--;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
 
}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "6. Connect  \n";
        cout << "7. Print friends of a person \n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin >> fileName;
            saveDB(fileName);
            // Save the network database into the file with the given name,
            // with each person saved in the format the save as printing out the person info,
            // and people are delimited similar to "networkDB.txt" format
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have "networkDB.txt" format
            // print format: one filename one line.
            // This step just shows all the available .txt file to load.
            cout << "Enter the name of the load file: "; 
            cin >> fileName;

            ifstream file(fileName);

            if(file){
                loadDB(fileName);
                            // If file is loaded successfully, also print the count of people in it: 
                cout << "Network loaded from " << fileName << " with " << count << " people \n";
            }
            else{
                // If file with name FILENAME does not exist: 
                cout << "File FILENAME does not exist!" << endl;
            }
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            Person *p = new Person();
            // Add a new Person ONLY if it does not exists!
            if(search(p) == NULL){
                cout << "Adding a new person \n";
                push_front(p);
            }
            else{
                cout << "Person already exists \n";
            }
        }
        else if (opt == 4){
            // TODO: Complete me!
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Person not found! \n";
            cout << "Removing a person \n";
            cout << "First name: ";
            cin >> fname;
            cout << "Last name: ";
            cin >> lname;

            if(search(fname, lname) == NULL){
                cout << "Person not found! \n";
            }
            else{
                remove(fname, lname);
            }
        }
        else if (opt==5){
            // TODO: Complete me!
            // print the people with the given last name
            // if not found: cout << "Person not found! \n";
            cout << "Print people with last name \n";
            cout << "Last name: ";
            cin >> lname;

            Person* ptr = head;
            int lastCount = 0;

            while(ptr != NULL){
                if(ptr->l_name == lname){
                    ptr->print_person();
                    lastCount++;
                }
                ptr=ptr->next;
            }
            if(!lastCount){
                cout << "Person not found! \n";
            }
        }
        else if(opt==6){
            cout << "Make friends \n";

            cout << "First friend \n";
            cout << "First name: ";
            cin >> fname;
            cout << "Last name: ";
            cin >> lname;

            if(search(fname, lname) == NULL){
                cout << "Person not found! \n";
            }
            else{
                string fname2, lname2;
                cout << "Second friend \n";
                cout << "First name: ";
                cin >> fname2;
                cout << "Last name: ";
                cin >> lname2;

                if(search(fname2, lname2) == NULL){
                    cout << "Person not found! \n";
                }
                else{
                    Person* first = search(fname, lname);
                    Person* second = search(fname2, lname2);
                    first->print_person();
                    second->print_person();
                    first->makeFriend(second);
                    second->makeFriend(first);
                }
            }

        }
        else if(opt == 7){
            cout << "Print friends of a person \n";
            cout << "First name: ";
            cin >> fname;
            cout << "Last name: ";
            cin >> lname;

            if(search(fname, lname) == NULL){
                cout << "Person not found! \n";
            }
            else{
                Person* personfriends = search(fname, lname);
                personfriends->pprint_friends();
            }
        }
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}

