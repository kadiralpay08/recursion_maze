#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>

using namespace std;

struct Coords{
    int x;
    int y;
};

struct Node{
   Node* next;
   Node* prev;
   Coords data;
};

class Q{
  public:
    Q(); // constructor
    ~Q(); //destructor
    bool isEmpty(); //Boolean that indicates if the queue has no elements
    void enqueue(Coords c); //elements are added
    Coords dequeue(); //elements are removed
    int size(); //provide the number of elements in the queue.

  private:
    Node* head;
    Node* tail;
};

#endif // QUEUE_H_INCLUDED
