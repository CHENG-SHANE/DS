#include <iostream>
using namespace std;

// struct a linked list 
// we need a node class to represent each element in the list
// each node has a data field and two pointers, one to the previous node and one to the next node
// doubly linked list class has a head and tail pointer
// head pointer points to the first node in the list and the tail pointer points to the last node in the list
// insertFront method inserts a new node at the front of the list
// insertBack method inserts a new node at the back of the list
// deleteNode method deletes a node with a given value from the list
// displayForward method displays the list from the head to the tail
// displayBackward method displays the list from the tail to the head
// main method creates a new doubly linked list, inserts some nodes, displays the list, deletes a node, and displays the list again

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int data): data(data), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList(): head(nullptr), tail(nullptr) {}

    // Destructor to free memory
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertFront(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertBack(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void deleteNode(int data) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == data) {
                if (temp->prev != nullptr) {
                    temp->prev->next = temp->next;
                }
                if (temp->next != nullptr) {
                    temp->next->prev = temp->prev;
                }
                if (temp == head) {
                    head = temp->next;
                }
                if (temp == tail) {
                    tail = temp->prev;
                }
                delete temp;
                return;
            }
            temp = temp -> next;
        }
    }

    void displayForward() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void displayBackward() {
        Node* temp = tail;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }
};

int main() {
    DoublyLinkedList list;
    list.insertFront(1);
    list.insertFront(2);
    list.insertBack(3);
    list.displayForward();  // Expect: 2 1 3
    list.displayBackward(); // Expect: 3 1 2
    list.deleteNode(1);
    list.displayForward();  // Expect: 2 3
    list.displayBackward(); // Expect: 3 2

    return 0;
}
