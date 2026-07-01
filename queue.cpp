#include "queue.h"

using namespace std;

Q::Q(){ // constructor
    head = nullptr;
    tail = nullptr;
}

Q::~Q(){ //destructor
    tail = nullptr;
    while (head != nullptr){
        Node* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
    }
}

bool Q::isEmpty(){ //Boolean that indicates if the queue has no elements
    if (head == nullptr){
        return true;
    }
    return false;
}

void Q::enqueue(Coords c){ //elements are added
    Node* newNode = new Node;
    newNode->data.x = c.x;
    newNode->data.y = c.y;
    newNode->next = nullptr;
    if (isEmpty()){
        newNode->prev = nullptr;
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = tail->next;
    }
}

Coords Q::dequeue(){ //elements are removed
    Coords temp;
    temp.x = -1;
    temp.y = -1;
    if (isEmpty()){
        return temp;
    }

    temp.x = head->data.x;
    temp.y = head->data.y;

    if (head->next == nullptr){
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }

    return temp;
}

int Q::size(){ //provide the number of elements in the queue.
    Node* temp = head;
    int count = 1;

    if (isEmpty()){
        return 0;
    }

    while (temp->next != nullptr){
        count++;
        temp = temp->next;
    }

    return count;
}
