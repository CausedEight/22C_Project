
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							      // number of nodes in tree

public:
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
    ~BinaryTree() { destroyTree(rootPtr); }
   
	
 	bool isEmpty() const	{return count == 0;}
	int getCount() const {return count;}
	
	bool insert(const ItemType &newData) = 0;
	bool search(const ItemType &target, ItemType &returnedItem) const;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);
	BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, const ItemType &target) const;
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
}; 

//Destroy the entire tree
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if(nodePtr) // != NULL
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        // cout << "DEBUG - Destructor: Now deleting " << nodePtr->getItem().getName() << endl;
        delete nodePtr;
    }
}  

 
template<class ItemType>
bool BinaryTree<ItemType>::search(const ItemType& target, ItemType& returnedItem) const {
    BinaryNode<ItemType>* temp = nullptr;
    temp = _search(this->rootPtr, target);
    if (temp) {
        returnedItem = target;
        return true;
    }
    return false;
}

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::_search(BinaryNode<ItemType>* treePtr, const ItemType& target) const{
    if (treePtr) {
        ItemType temp = treePtr->getItem();
        if (temp == target) {
            return treePtr;
        }
        else if (temp < target) {
            _search(treePtr->getRightPtr(), target);
        }
        else {
            _search(treePtr->getLeftPtr(), target);
        }
    }
    else {
        return treePtr;
    }
    
}

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
    BinaryNode<ItemType>* newNodePtr)
{
    BinaryNode<ItemType>* pWalk = nodePtr, * parent = nullptr;

    if (!nodePtr) // == NULL
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }
    else
    {
        while (pWalk) // != NULL
        {
            parent = pWalk;
            if (pWalk->getItem() > newNodePtr->getItem())
                pWalk = pWalk->getLeftPtr();
            else
                pWalk = pWalk->getRightPtr();
        }
        if (parent->getItem() > newNodePtr->getItem())
            parent->setLeftPtr(newNodePtr);
        else
            parent->setRightPtr(newNodePtr);
    }

    return nodePtr;
}


template<class ItemType>
bool BinaryTree<ItemType>::insert(const ItemType& newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    return true;
}

#endif

