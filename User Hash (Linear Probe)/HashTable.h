#pragma once
#pragma once
// Specification file for the Hash class
// Written By: A. Student
// Changed by: Omid Vasseghi


#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"

using std::string;


template<class ItemType>
class HashTable
{
private:
    HashNode<ItemType>* hashAry;
    int hashSize;
    int count;
    static int totalCollisions;
    static int longestPath;

public:
    HashTable() { count = 0; hashSize = 67; hashAry = new HashNode<ItemType>[hashSize]; } //hashSize = next prime number after the # of entries in input x 2 
    HashTable(int n) { count = 0; hashSize = n;	hashAry = new HashNode<ItemType>[hashSize]; }
    ~HashTable() { delete[] hashAry; }

    int getLongestpath() const { return longestPath; }
    int getTotalCollisions() const { return totalCollisions; }
    int getCount() const { return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const { return 100.0 * count / hashSize; }
    bool isEmpty() const { return count == 0; }
    bool isFull()  const { return count == hashSize; }

    bool insert(const ItemType& itemIn, int h(const ItemType& key, int size));
    bool remove(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size));
    int  search(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size)) const;
    void displayHashTable() const;
};
template<class ItemType>
int HashTable<ItemType>::totalCollisions = 0;

template<class ItemType>
int HashTable<ItemType>::longestPath = 0;
/*~*~*~*
   Insert an item into the hash table
   It does not reject duplicates
*~**/
template<class ItemType>
bool HashTable<ItemType>::insert(const ItemType& itemIn, int h(const ItemType& key, int size))
{
    if (count == hashSize)
        return false;

    int index = h(itemIn, hashSize);
    int collisions = 0;
    int firstDeleted = -1;

    while (hashAry[index].getOccupied() != 0)
    {
        if (hashAry[index].getOccupied() == 1 && hashAry[index].getItem().getIpAddress() == itemIn.getIpAddress())
            return false;

        if (firstDeleted == -1 && hashAry[index].getOccupied() == -1)
            firstDeleted = index;

        index = (index + 1) % hashSize;
        collisions++;
    }

    if (firstDeleted != -1)
        index = firstDeleted;

    totalCollisions += collisions;

    hashAry[index].setItem(itemIn);
    hashAry[index].setOccupied(1);
    hashAry[index].setNoCollisions(collisions);
    count++;

    if (collisions > longestPath)
        longestPath = collisions;

    return true;
}


/*~*~*~*
   Removes the item with the matching key from the hash table
   if found:
     - copies data in the hash node to itemOut
     - replaces data in the hash node with an empty record (occupied = -1: deleted!)
     - returns true
   if not found:
     - returns false
*~**/
template<class ItemType>
bool HashTable<ItemType>::remove(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size))
{
    int index = h(key, hashSize);
    int collisions = 0;

    while (hashAry[index].getOccupied() != 0)
    {
        if (hashAry[index].getOccupied() == 1 && hashAry[index].getItem().getIpAddress() == key.getIpAddress())
        {
            itemOut = hashAry[index].getItem();
            hashAry[index].setOccupied(-1);
            count--;
            return true;
        }

        index = (index + 1) % hashSize;
        collisions++;
    }

    return false;
}


/*~*~*~*
   hash search - linear probe
   if found:
      - copy data to itemOut
      - returns the number of collisions for this key
   if not found, returns -1
*~**/
template<class ItemType>
int HashTable<ItemType>::search(ItemType& itemOut, const ItemType& key, int h(const ItemType& key, int size)) const
{
    int hashValue = h(key, hashSize);
    int index = hashValue;
    int collisions = 0;

    while (hashAry[index].getOccupied() != 0)
    {
        if (hashAry[index].getOccupied() == 1 && hashAry[index].getItem().getIpAddress() == key.getIpAddress())
        {
            itemOut = hashAry[index].getItem();
            return collisions;
        }

        index = (index + 1) % hashSize;
        collisions++;

        // If we have looped through the entire table and reached the initial hash value again,
        // it means the key was not found and we break the loop to prevent an infinite loop.
        if (index == hashValue)
            break;
    }

    return -1;
}
template<class ItemType>
void HashTable<ItemType>::displayHashTable() const {
    for (int index = 0; index < hashSize; ++index) {
        if (hashAry[index].getOccupied() == 1) {
            std::cout << "Index " << index << ": " << hashAry[index].getItem().getIpAddress() << std::endl;
        }
        else {
            std::cout << "Index " << index << ": EMPTY" << std::endl;
        }
    }
}
#endif // HASHTABLE_H_
