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

int main()
{
    HashTable<User> hash;

    buildHash(hash);
    cout << "Load Factor: " << hash.getLoadFactor() << endl;

    return 0;
}
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
            }
            else
            {
                cout << "Invalid input format: " << line << endl;
            }
        }

        inputFile.close();
    }

