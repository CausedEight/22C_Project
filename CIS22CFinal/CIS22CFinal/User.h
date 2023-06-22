//
//  User.hpp
//  CIS22CFinal
//
//  Created by Slava Miroshnichenko on 6/20/23.
//

#ifndef User_h
#define User_h

#include<iostream>
#include<string>

using std::string;

class User;
int hashFunc(const User& key, int size);

class User
{
private:
    string ipAddress; // primary key
    string name;
    string continent;
    string website;
    int hour;
    int minute;

public:
    // Default constructor
    User()
    {
        // Default initialization of member variables
        hour = 0;
        minute = 0;
    }

    // Parameterized constructor
    User(string ip, string n, string c, string w, int h, int m)
        : ipAddress(ip), name(n),continent(c), website(w), hour(h), minute(m)
    {
        // Initialization of member variables with provided values
    }

    // Getters
    string getIpAddress() const { return ipAddress; }
    string getName() const { return name; }
    string getCont() const {return continent;}
    string getWebsite() const { return website; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }

    // Setters
    void setIpAddress(string ip) { ipAddress = ip; }
    void setName(string n) { name = n; }
    void setContinent(string c) { continent = c; }
    void setWebsite(string w) { website = w; }
    void setHour(int h) { hour = h; }
    void setMinute(int m) { minute = m; }

    // Overloaded operators
    bool operator > (const User& right) { return (ipIntoInt(this->ipAddress) > ipIntoInt(right.ipAddress)); } // Overloaded >
    bool operator < (const User& right) { return (ipIntoInt(this->ipAddress) < ipIntoInt(right.ipAddress)); } // Overloaded <
    bool operator == (const User& right) { return (ipIntoInt(this->ipAddress) == ipIntoInt(right.ipAddress)); } // Overloaded ==
    
    friend std::ostream& operator<<(std::ostream& os, const User& dt);

    // Friend function declarations
    friend void hDisplay(const User&);
    friend void iDisplay(const User&, int);

    int ipIntoInt(string ip) { return stoi(ip); }
    friend int hashFunc(const User& key, int size);

};

#endif /* User_hpp */
