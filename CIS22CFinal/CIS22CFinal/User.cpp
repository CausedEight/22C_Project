#include<string>
#include "User.h"
#include <iostream>

/*~*~*~*
 Hash function: takes the key and returns the index in the hash table
 *~**/
// _hash
int hashFunc(const User &key, int size){
    string k = key.getName();
    int sum = 0;
    for (int i = 0; k[i]; i++)
        sum += k[i];
    return sum % size;
}

std::ostream& operator<<(std::ostream& os, const User& dt){
    std::cout << "*********************************" << std::endl;
    std::cout << "Name: " << dt.getName() << std::endl;
    std::cout << "Location: " << dt.getCont() << std::endl;
    std::cout << "IP: " << dt.getIpAddress() << std::endl;
    std::cout << "Time: " << dt.getHour() << ":" << dt.getMinute() << std::endl;
    std::cout << "Request: " << dt.getWebsite() << std::endl;
    return os;
}
