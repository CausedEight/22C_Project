#include <iostream>
#include <fstream>
#include <sstream>

#include "HashTable.h"
#include "User.h"

using namespace std;

void buildHash(HashTable<User>& hash);
void searchManager(const HashTable<User>& hash);
void deleteManager(HashTable<User>& hash);
void insertManager(HashTable<User>& hash);
void display(HashTable<User>& hash);



int main()
{
    HashTable<User> hash;

    buildHash(hash);
    cout << "Load Factor: " << hash.getLoadFactor() << endl;
    cout << "Total Collisions building hash: " << hash.getTotalCollisions() << endl;
    cout << "Longest collision path: " << hash.getLongestpath() << endl;
    //searchManager(hash);
    //deleteManager(hash);
    insertManager(hash);
    cout << "Displayed Hash Table:\n";
    hash.displayHashTable();

    return 0;
}
/* **************************************************
This function builds a hash table with data from an array
It calls the insert() function that inserts the new data at the right location in the hash table.
************************************************** */
void buildHash(HashTable<User>& hash)
{
 
        ifstream inputFile("input.txt");

        if (!inputFile.is_open())
        {
            cout << "Failed to open input file." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string ipAddress, name, city, state, website;
            int hour, minute;
            if (getline(iss, ipAddress, ',') &&
                getline(iss, name, ',') &&
                getline(iss, city, ',') &&
                getline(iss, state, ',') &&
                getline(iss, website, ',') &&
                iss >> hour &&
                iss.ignore() &&
                iss >> minute)
            {
                User user(ipAddress, name, city, state, website, hour, minute);
                hash.insert(user, hashFunc);
                //cout << ipAddress << name << city << state << website << hour << minute << endl;
            }
            else
            {
                cout << "Invalid input format: " << line << endl;
            }
        }

        inputFile.close();
}
/* **************************************************
This function searches a hash table with user provided data.
It calls the hash search function in a loop.
To stop searching enter "#"
************************************************** */
void searchManager(const HashTable<User>& hash)
{
    cout << endl << "~*~ Test Search ~*~" << endl;
    cout << "Enter ipAddress [# to stop searching]:" << endl;
    string ip;
    getline(cin, ip);
    while (ip != "#")
    {
        User item;
        int nc = hash.search(item, User(ip, "", "", "", "", 0, 0), hashFunc);
        if (nc != -1)
        {
            cout << item.getName() << " " << item.getIpAddress() << " (" << nc << " collisions!)" << endl;
        }
        else
        {
            cout << ip << " not found!" << endl;
        }
        getline(cin, ip);
    }
    cout << "Load Factor: " << hash.getLoadFactor() << endl;
}
/* **************************************************
This function deletes user provided data data from a hash table
It calls the hash delete function in a loop.
To stop deleting enter "#"
************************************************** */
void deleteManager(HashTable<User>& hash)
{
    cout << endl << "~*~ Test Delete ~*~" << endl;
    cout << "Enter ipAddress [# to stop deleting]:" << endl;
    string ip;
    getline(cin, ip);
    while (ip != "#")
    {
        User itemOut;
        if (hash.remove(itemOut, User(ip, "", "", "", "", 0, 0), hashFunc))
        {
            cout << itemOut.getName() << " " << itemOut.getIpAddress() << " - deleted!" << endl;
        }
        else
        {
            cout << ip << " not found!" << endl;
        }
        getline(cin, ip);
    }
    cout << "Load Factor: " << hash.getLoadFactor() << endl;
}
/* **************************************************
This function inserts user provided data into the hash table
It rejects duplicates.
It calls hash search and hash insert in a loop.
To stop getting user input enter "#"
************************************************** */
void insertManager(HashTable<User>& hash)
{
    cout << endl << "~*~ Test Insert - reject duplicates ~*~" << endl;
    cout << "Enter an ipAddress [# to stop reading]:" << endl;
    string ip;
    getline(cin, ip);
    while (ip != "#")
    {
        User found;
        if (hash.search(found, User(ip, "", "", "", "", 0, 0), hashFunc) != -1)
        {
            cout << "Duplicate key: " << found.getIpAddress() << " - rejected!" << endl;
        }
        else
        {
            string fullName, city, state, website;
            int hour, minute;


            cout << "Enter full name: ";
            getline(cin, fullName);

            cout << "Enter city: ";
            getline(cin, city);

            cout << "Enter state: ";
            getline(cin, state);

            cout << "Enter website: ";
            getline(cin, website);

            cout << "Enter hour: ";
            cin >> hour;

            cout << "Enter minute: ";
            cin >> minute;

            cin.ignore();

            cout << "User Created : \n";
            cout << "IP address: " << ip << endl;
            cout << "Full name: " << fullName << endl;
            cout << "City: " << city << endl;
            cout << "Website: " << website << endl;
            cout << "Minute: " << minute << endl;
            cout << "Hour: " << hour << endl;
            
            cout << "Press enter to insert this user.\n";
            cin.ignore();

            User newStudent(ip,fullName,city,state,website,minute,hour);
            hash.insert(newStudent, hashFunc);
            cout << fullName << " - inserted (" << hash.search(found, newStudent, hashFunc) << " collisions)" << endl;
        }
        cout << "Enter name [# to stop reading]:" << endl;
        getline(cin, ip);
    }
    cout << "Load Factor: " << hash.getLoadFactor() << endl;
}

