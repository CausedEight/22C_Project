/*
 Hash Tables ADT - Linear Probe
 Written by, Slava, Tauhid, Omid, Jaden, Hamza
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <sstream>
#include "HashTable.h"
#include "BinaryST.h"
#include "User.h"

#include <ctime>
#include <chrono>
#include <random>
#include "HashTable.h"
#include "BinaryST.h"
#include "User.h"

using namespace std;

void searchManager(const HashTable<User> &hash); // can be done useing bst
void displayManager(const BinaryTree<User> &);

template <class ItemType>
void hDisplay (ItemType &item);
template <class ItemType>
void iDisplay(ItemType &item, int level);

void userUI(HashTable<User> &, BinaryTree<User> &);
string decideCont(string ip);
void generateIP(string &);

int hashFunc(const User& key, int size);

void undoDelete(HashTable<User> &hash, BinarySt<string> &bst, Stack<User> &stck){
    if (stck.isEmpty()){
        cout << "No recently Deleted Users." << endl;
    }else{
        User newUser = stck.pop();
        bst.insert(newUser.getName());
        hash.insert(newUser,hashFunc);
        cout << newUser.getName() << "added back to list." << endl;
    }
}


int main(){
    HashTable <User> hash;
    BinaryTree<User> tree;
    userUI(hash, tree);
    //displayManager(hash);
    displayManager(tree);
    searchManager(hash);
    return 0;
}

void userUI(HashTable<User> &hash, BinaryTree<User> &tree){
    for (int i = 0 ; i < 15; i++){
        cout << "*";
    }
    cout << endl;
    cout << "Welcome user!" << endl;
    for (int i = 0 ; i < 15; i++){
        cout << "*";
    }
    cout << endl;
    cout << "Lets start with a name: ";
    string name, ip;
    getline(cin, name);
    cout << "If you know, enter your IP (worry not if you dont know, one will be assigned to you. Just press enter): ";
    getline(cin, ip);
    if (ip.empty()){
        generateIP(ip);
    }
    cout << ip << endl;
    string cont = decideCont(ip);
    
    cout << "Which website are you trying to reach today? ";
    string website;
    getline(cin, website);
    
    chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t currentTime = std::chrono::system_clock::to_time_t(now);
    tm* timeInfo = localtime(&currentTime);
    int hour = timeInfo->tm_hour;
    int minutes = timeInfo->tm_min;
    
    User newUser(ip, name, cont, website, hour, minutes);
    hash.insert(newUser, hashFunc);
    tree.insert(newUser);
}
/* **************************************************
This function searches a hash table with user provided data.
It calls the hash search function in a loop.
To stop searching enter "#"
************************************************** */

void searchManager(const HashTable<User> &hash){
    cout << endl << "~*~ Test Search ~*~" << endl;
    cout << "Enter IP [# to stop searching]:" << endl;
    string ip;
    getline(cin, ip);
    
    //Getting the time
    chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t currentTime = std::chrono::system_clock::to_time_t(now);
    tm* timeInfo = localtime(&currentTime);
    int hour = timeInfo->tm_hour;
    int minutes = timeInfo->tm_min;
    /** * * * * * * * * * * * * * * * * * * * * * * */
    while (ip != "#"){
        User item;
        User keyItem(ip, "", "Unknown", "Unknown", hour, minutes); // Ip, name, continent, website
        int nc = hash.search(item, keyItem, hashFunc);
        if (nc != -1){
            cout << item.getName() << " " << item.getIpAddress() << "(" << nc << " collisions!)" << endl;
        }else
        {
            cout << ip << " not found!" << endl;
        }
        getline(cin, ip);
    }
    cout << "Load Factor: " << hash.getLoadFactor() << endl;
}

/*
Display manager: traversals, count, indented tree, and inner nodes
Input Parameter: bst
*/

void displayManager(const BinaryTree<User> &bst){
    
    string option;
    // count
        cout << "Display count [Y/N]?" << endl;
        getline(cin, option);
        option[0] = toupper(option[0]);
        if (option == "Y")
        {
            cout << "The number of nodes in the BST is ";
            cout << bst.getCount()<< endl;
        }
        
        // traversals
        cout << "Display Tree [In/Pre/posT/N]?" << endl;
        getline(cin, option); // I, P, T or N
        option[0] = toupper(option[0]);
        switch (option[0])
        {
            case 'I':
                cout << endl << "Inorder:" << endl;
                /* Write your code here: call inorder - use hDisplay */
                bst.inOrder(hDisplay);
                cout << endl;
                break;
            case 'P':
                cout << endl << "Preorder:" << endl;
                /* Write your code here: call preorder - use hDisplay */
                bst.preOrder(hDisplay);
                cout << endl;
                break;
            case 'T':
                cout << endl << "Postorder:" << endl;
                /* Write your code here: call postorder - use hDisplay */
                bst.postOrder(hDisplay);
                cout << endl;
                break;
            case 'N':
                break;
            default:
                cout << "Invalid option!" << endl;
                        break;
                    }

                // Indented Tree
                cout << "Display Indented List [Y/N]?" << endl;
                getline(cin, option);
                option[0] = toupper(option[0]);
                if (option == "Y")
                {
                    cout << "Indented List:" << endl;
                    /* Write your code here: call printTree - use iDisplay */
                    bst.printTree(iDisplay);
                    cout << endl;
                }
}

template <class ItemType>
void iDisplay(ItemType &item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item << endl;
    
}

template <class ItemType>
void hDisplay (ItemType &item)
{
    cout << item << " ";
}

string decideCont(string ip){
    int number1 = ip[0];
    int number2 = ip[1];
    int number3 = ip[2];
    
    
    int geoNum = number1 + number2 + number3;
    
    if (geoNum < 43){
        return "NA";
    }else if (geoNum < 86){
        return "SA";
    }else if (geoNum < 129){
        return "EU";
    }else if (geoNum < 172){
        return "AF";
    }else if (geoNum < 215){
        return "AS";
    }else{
        return "OC";
    }
}

void generateIP(string &ip){
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 255);
    for (int i = 1; i <= 4; i++){
        int randomNumber = distribution(generator);
        ip.append(to_string(randomNumber));
    }
}

int hashFunc(const User& key, int size)
{
    string ipAddress = key.getIpAddress();
    int sum = 0;
    for (int i = 0; ipAddress[i]; i++)
        sum += ipAddress[i];
    return sum % size;
};

