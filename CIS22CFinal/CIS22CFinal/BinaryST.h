//
//  BinaryST.h
//  CIS22CFinal
//
//  Created by Slava Miroshnichenko on 6/20/23.
//

#ifndef BinaryST_h
#define BinaryST_h

#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;        // ptr to root node
    int count;                                  // number of nodes in tree

public:
    BinaryTree() {rootPtr = 0; count = 0;}
    BinaryTree(const BinaryTree<ItemType> & tree){ }
    ~BinaryTree() { destroyTree(rootPtr); }
   
    
    bool isEmpty() const    {return count == 0;}
    int getCount() const {return count;}
    
    bool insert(const ItemType &newData);
    bool search(const ItemType &target, ItemType &returnedItem) const;
    bool remove(const ItemType &target);
    
    void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
    void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
    void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
    void printTree(void visit(ItemType &, int)) const{_printTree(visit, rootPtr, 1);}

    bool findSmallest(BinaryNode<ItemType>* nodePtr, ItemType& returnedItem) const;

private:
    //Delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);
    BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, const ItemType &target) const;
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType& target);
    void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _printTree(void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const;

    BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* nodePtr, ItemType& smallest) const;
    
   
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
        count--;
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
bool BinaryTree<ItemType>::insert(const ItemType& newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    count++;
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::findSmallest(BinaryNode<ItemType>* nodePtr, ItemType& returnedItem) const
{
    BinaryNode<ItemType>* temp = nullptr;
    if (nodePtr == nullptr)
        return false;

    temp = _findSmallest(nodePtr, returnedItem);
    if (temp) // != NULL
        return true;
    return false;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &target) {
    BinaryNode<ItemType>* temp = _remove(this->rootPtr, target);
    if (temp == nullptr)
        return false;

    return true;
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


//Preorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    /* Write your code here */
    if (nodePtr){
        ItemType item = nodePtr->getItem();
        visit(item);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
    }

}

//Inorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

//Postorder Traversal
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    /* Write your code here */
    if (nodePtr){
        ItemType item = nodePtr->getItem();
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
        visit(item);
    }
}
template<class ItemType>
void BinaryTree<ItemType>::_printTree(void visit(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const
{
     if (nodePtr){
        ItemType item = nodePtr->getItem();
        visit(item, level);
        _printTree(visit, nodePtr->getRightPtr(), level+1);
        _printTree(visit, nodePtr->getLeftPtr(), level+1);
     }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findSmallest(BinaryNode<ItemType>* nodePtr, ItemType& smallest) const
{
    if (nodePtr) {
        BinaryNode<ItemType>* temp = nodePtr;
        while (temp->getLeftPtr() != nullptr)
            temp = temp->getLeftPtr();
        smallest = temp->getItem();
        return temp;
    }
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, const ItemType &target) {
    if (nodePtr == nullptr)
        return nodePtr;
    else if (target < nodePtr->getItem())
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target));
    else if (target > nodePtr->getItem())
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target));
    else {
        // Case 1:  No child
        if (nodePtr->isLeaf()) {
            delete nodePtr;
            nodePtr = nullptr;
        }
        //Case 2: One child 
        else if (nodePtr->getLeftPtr() == nullptr) {
            BinaryNode<ItemType>* temp = nodePtr;
            nodePtr = nodePtr->getRightPtr();
            delete temp;
        }
        else if (nodePtr->getRightPtr() == nullptr) {
            BinaryNode<ItemType>* temp = nodePtr;
            nodePtr = nodePtr->getLeftPtr();
            delete temp;
        }
        // case 3: 2 children
        else {
            ItemType temp;
            findSmallest(nodePtr->getRightPtr(), temp);
            nodePtr->setItem(temp);
            nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), temp));
        }
    }

    this->rootPtr = nodePtr;
    return nodePtr;

}

#endif /* BinaryST_h */
