//  Created by Melih Kurtaran on 05/04/2019.
//  Copyright © 2019 melihkurtaran. All rights reserved.

#include <iostream>
#include <chrono>
#include <random>

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;
using namespace std;

struct Node {
    
    Node(int k, Node* n, Node* p)
    :key(k),next(n),prev(p){};
    
    int key;
    Node* next;
    Node* prev;
};

void randomSeq(Node* &head, int size)
{
    if(head != nullptr)
    {
        while(head->next != nullptr)
        {
            head = head->next;
            delete head->prev;
        }
        delete head;
    }
    mt19937 rng;
    uniform_int_distribution<uint32_t> uint_dist(1,size);
    head = new Node(uint_dist(rng),nullptr,nullptr);
    Node *ptr = head;
    for(int i=1;i<size;i++)
    {
        ptr->next = new Node(uint_dist(rng),nullptr,ptr);
        ptr = ptr->next;
    }
}

void increasingSeq(Node* &head, int size)
{
    head = new Node(1,nullptr,nullptr);
    Node *ptr = head;
    for(int i=1;i<size;i++)
    {
        ptr->next = new Node(i+1,nullptr,ptr);
        ptr = ptr->next;
    }
}

void printLinkedList(Node* head)
{
    Node *ptr = head;
    cout << endl;
    while(ptr != nullptr)
    {
        cout << ptr->key << " ";
        ptr = ptr->next;
    }
    cout << endl << endl;
}

void isSorted(Node* head)
{
    bool isSorted = true;
    Node* ptr = head;
    while(ptr != nullptr && ptr->next != nullptr)
    {
        if(ptr->next->key < ptr->key)
        {
            cout <<"The array is NOT sorted."<< endl << endl;
            isSorted = false;
            break;
        }
        ptr = ptr->next;
    }
    if(isSorted)
        cout <<"The array is sorted."<< endl << endl;
}

Node * partition(Node* &head, Node* start, Node* end)
{
    int temp;
    int pe = start->key;
    Node * l = start;
    Node * r = end;
    bool l_r_met = false;
    while(!l_r_met)
    {
        while(l->key <= pe && l != end)
        {
            l = l->next;
            if(l==r)
                l_r_met = true;
        }
        while(r->key >= pe && r != start)
        {
            r = r->prev;
            if(l==r)
                l_r_met = true;
        }
        if(!l_r_met)
        {
            temp = l->key;
            l->key = r->key;
            r->key = temp;
        }
    }
    temp = start->key;
    start->key = r->key;
    r->key = temp;
    return r;
}

void quicksort(Node* &head, Node* firstPointer, Node* lastPointer)
{
    Node* q;
    if(firstPointer != lastPointer)
    {
        q = partition(head,firstPointer,lastPointer);
        if(firstPointer != q)
            quicksort(head,firstPointer,q->prev);
        if(lastPointer != q)
            quicksort(head,q->next,lastPointer);
    }
}

int main()
{
    int operation = 0, size;
    cout << "Enter the size of doubly linked list: ";
    cin >> size;
    Node *head = nullptr;
    
    while(operation != 6)
    {
        cout << "Quicksort – operation:" << endl
        << "1) Generate random sequence"<< endl
        << "2) Generate increasing sequence"<< endl
        << "3) Print current sequence"<< endl
        << "4) Check if list is increasing (sorted)"<< endl
        << "5) Quicksort"<< endl
        << "6) End" << endl << endl
        << "Operation: ";
        cin >> operation;
        
        switch (operation) {
            case 1:
                randomSeq(head,size);
                break;
            case 2:
                increasingSeq(head,size);
                break;
            case 3:
                printLinkedList(head);
                break;
            case 4:
                isSorted(head);
                break;
            case 5:
            {
                Node *tail = head;
                while(tail->next != nullptr)
                    tail = tail->next;
                quicksort(head,head,tail);
                cout << endl << "Quicksort is done." << endl << endl;
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
