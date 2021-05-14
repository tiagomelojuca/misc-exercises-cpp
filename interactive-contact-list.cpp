#include <iostream>
#include <fstream>
#include <string>
#include <map>

void list_contacts(std::map<std::string, std::string> &contact_list) {
    
    int n = 1;

    for(std::map<std::string, std::string>::iterator it = contact_list.begin();
        it != contact_list.end();
        ++it)
    {
        std::string name = it->first;
        std::string phone = it->second;

        std::cout << n << ". " << name << "\tPhone: " << phone << std::endl;

        n++;
    }

    std::cout << "Contacts total: " << contact_list.size() << std::endl;

}

void search_contacts(std::map<std::string, std::string> &contact_list) {

    std::string name_pattern;

    std::cout << "Type the name you are looking for: ";
    getline(std::cin, name_pattern);

    int n = 1;

    for(std::map<std::string, std::string>::iterator it = contact_list.begin();
        it != contact_list.end();
        ++it)
    {
        std::string name = it->first;
        std::string phone = it->second;

        if(name.find(name_pattern) != -1) {
            std::cout << n << ". " << name << "\tPhone: " << phone << std::endl;
            n++;
        }

    }

    std::cout << "Contacts found: " << (n-1) << std::endl;

}

void add_contact(std::map<std::string, std::string> &contact_list) {

    std::string name, phone;

    std::cout << "Name: ";
    getline(std::cin, name);

    std::cout << "Phone: ";
    getline(std::cin, phone);

    if (contact_list.find(name) != contact_list.end()) {
        std::cout << "Contact updated!" << std::endl;
    } else {
        std::cout << "Contact inserted!" << std::endl;
    }

    contact_list[name] = phone;

}

void remove_contact(std::map<std::string, std::string> &contact_list) {

    std::string name;

    std::cout << "Name: ";
    getline(std::cin, name);

    std::map<std::string, std::string>::iterator it = contact_list.find(name);

    if (it != contact_list.end()) {
        std::cout << "Contact removed" << std::endl;
        contact_list.erase(it);
    } else {
        std::cout << "Contact not found" << std::endl;
    }

}

void save_contacts(std::map<std::string, std::string> &contact_list) {

    std::string file_name;

    std::cout << "Please type the file name: ";
    getline(std::cin, file_name);

    std::fstream file_contact_list(file_name.c_str(), std::fstream::out | std::fstream::trunc);

    if (!file_contact_list.is_open()) {
        std::cout << "Couldn't open the specified file" << std::endl;
        return;
    }

    int n = 1;

    for(std::map<std::string, std::string>::iterator it = contact_list.begin();
        it != contact_list.end();
        ++it)
    {
        std::string name = it->first;
        std::string phone = it->second;

        file_contact_list << n << ". " << name << "\tPhone: " << phone << std::endl;

        n++;
    }

    std::cout << "Saved contacts: " << contact_list.size() << std::endl;

}

void command_loop(std::map<std::string, std::string> &contact_list) {

    char operation;

    do {
        std::cout << "Choose an option:" << std::endl
                  << "(l)ist, (s)earch, (a)dd, (r)emove, (w)rite, (q)uit"
                  << std::endl
                  << std::endl;

        std::cin >> operation;
        std::cin.ignore();

        switch (operation) {
            case 'l':
            case 'L':
                list_contacts(contact_list);
                break;
            case 's':
            case 'S':
                search_contacts(contact_list);
                break;
            case 'a':
            case 'A':
                add_contact(contact_list);
                break;
            case 'r':
            case 'R':
                remove_contact(contact_list);
                break;
            case 'w':
            case 'W':
                save_contacts(contact_list);
                break;
            case 'q':
            case 'Q':
                return;                
            default:
                std::cout << "Unknown operation" << std::endl;
        }
    } while (operation != 'q');

}

int main() {

    std::map<std::string, std::string> contact_list;

    std::cout << "Welcome to your interactive contact list!" << std::endl;
    command_loop(contact_list);
    return 0;

}
