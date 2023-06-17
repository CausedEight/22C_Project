#include<string>
#include "User.h"

/*~*~*~*
 Hash function: takes the key and returns the index in the hash table
 *~**/
int hashFunc(const User& key, int size)
{
    string ipAddress = key.getIpAddress();
    int sum = 0;
    for (int i = 0; ipAddress[i]; i++)
        sum += ipAddress[i];
    return sum % size;
};
