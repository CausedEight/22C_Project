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
// #include "HashTable.h"
// #include "BinarySearchTree.h"
// #include "User.h"

using namespace std;

void searchManager(const HashTable<User> &hash); // can be done useing bst
void displayManager(const BinarySearchTree<User> &);

int main(){
    HashTable <User> hash;
    displayManager(hash);
    searchManager(hash);
    return 0;
}

/* **************************************************
This function searches a hash table with user provided data.
It calls the hash search function in a loop.
To stop searching enter "#"
************************************************** */
void searchManager(const HashTable<User> &hash){
    cout << endl << "~*~ Test Search ~*~" << endl;
    cout << "Enter name [# to stop searching]:" << endl;
    string name;
    getline(cin, name);
    while (name != "#"){
        User item;
        User keyItem(0, name, "Unknown", "Unknown"); // Ip, name, continent, website
        int nc = hash.search(item, keyStudent, key_to_student);\
        if (nc != -1){
            cout << item.getName() << " " << item.getIp() << "(" << nc << " collisions!)" << endl;
        }else
        {
            cout << name << " not found!" << endl;
        }
        getline(cin, name);
    }
    cout << "Load Factor: " << hash.getLoadFactor() << endl;
}

/*
Display manager: traversals, count, indented tree, and inner nodes
Input Parameter: bst
*/

void displayManager(const BinarySearchTree<User> &bst){
    
    string option;
    // count
        cout << "Display count [Y/N]?" << endl;
        getline(cin, option);
        option[0] = toupper(option[0]);
        if (option == "Y")
        {
            cout << "The number of nodes in the BST is ";
            cout << /* Write your code here: call getCount */ bst.getCount()<< endl;
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
                
                // Inner Nodes
                cout << "Display Inner Nodes [Y/N]?" << endl;
                getline(cin, option);
                option[0] = toupper(option[0]);
                if (option == "Y")
                {
                    cout  << "Inner Nodes:" << endl;
                    /* Write your code here: call printInnerNodes - use kDisplay */
                    bst.printInnerNodes(kDisplay);
                    cout << endl;
                }
                    
}
