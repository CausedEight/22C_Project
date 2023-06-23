#ifndef Stack_h
#define Stack_h

template <class T>
class Stack
{
private:
    // Structure for the stack nodes
    struct StackNode
    {
      T value;          // Value in the node
      StackNode *next;  // Pointer to next node
    };

    StackNode *top;     // Pointer to the stack top
    int length;

public:
    Stack(){ top = NULL; length = 0; }
    ~Stack();

    // Stack operations:
    bool push(T);
    T pop();
    T peek() {return top->value;}
    bool isEmpty() {return top==NULL;}
    int getLength() {return length;}
};

// inserts argument onto stack
template <class T>
bool Stack<T>::push(T item)
{
   StackNode *newNode;

   // Allocate a new node and store item there.
   newNode = new StackNode;
   if (!newNode)
       return false;
   newNode->value = item;

   // Update links and counter
   newNode->next = top;
   top = newNode;
   length++;

   return true;
}

//Deletes the value at the top of stack and returns it.
//Assume stack is NOT empty.
template <class T>
T Stack<T>::pop(){
    StackNode* temp = new StackNode;
    temp = top->next;
    T s = top->value;
    delete top;
    top = temp;
    --length;
    return s;
}

//Traverses the list & deletes each node
template <class T>
Stack<T>::~Stack() {
    StackNode* iter = top;
    while(iter!=NULL){
        iter = iter->next;
        delete top;
        top = iter;
    }
}

#endif /* Stack_h */
