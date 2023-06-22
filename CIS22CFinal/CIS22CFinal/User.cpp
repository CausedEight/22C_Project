#include<string>
#include "User.h"
#include <iostream>

/*~*~*~*
 Hash function: takes the key and returns the index in the hash table
 *~**/

std::ostream& operator<<(std::ostream& os, const User& dt){
    std::cout << "*********************************" << std::endl;
    std::cout << "Name: " << dt.getName() << std::endl;
    std::cout << "Location: " << dt.getCont() << std::endl;
    std::cout << "IP: " << dt.getIpAddress() << std::endl;
    std::cout << "Time: " << dt.getHour() << ":" << dt.getMinute() << std::endl;
    std::cout << "Request: " << dt.getWebsite() << std::endl;
    return os;
}
