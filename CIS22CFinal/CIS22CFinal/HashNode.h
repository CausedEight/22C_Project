//
//  HashNode.h
//  CIS22CFinal
//
//  Created by Slava Miroshnichenko on 6/20/23.
//

#ifndef HashNode_h
#define HashNode_h
template <typename T>
class HashNode
{
private:
    T item;
    int occupied;    // 1 -> occupied, 0 -> empty from start, -1 -> empty after removal
    int noCollisions;

public:
    // constructors
    HashNode() { occupied = 0; noCollisions = 0; }
    HashNode(T anItem) { item = anItem; occupied = 1; noCollisions = 0; }
    HashNode(T anItem, int ocp, int nCol)
    {
        item = anItem; occupied = ocp; noCollisions = nCol;
    }

    // setters
    void setItem(const T& anItem) { item = anItem; }
    void setOccupied(int ocp) { occupied = ocp; }
    void setNoCollisions(int nCol) { noCollisions = nCol; }

    // getters
    T getItem() const { return item; }
    int getOccupied() const { return occupied; }
    int getNoCollisions() const { return noCollisions; }
};

#endif /* HashNode_h */
