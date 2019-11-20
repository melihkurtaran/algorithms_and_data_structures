//  Created by Melih Kurtaran on 20/03/2019.
//  Copyright © 2019 melihkurtaran. All rights reserved.

#include <iostream>

using namespace std;

struct Node{
    Node(int key): key(key){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
    
    int key;
    Node* parent;
    Node* left;
    Node* right;
};

void insertToTree(Node * &root, Node *toBeInserted)
{
    Node *ptr = root;
    if(root == nullptr)
        root = toBeInserted;
    else
    {
        while(ptr != nullptr)
        {
            if(ptr->key > toBeInserted->key)
            {
                if(ptr->left != nullptr)
                    ptr = ptr->left;
                else
                {
                    ptr->left = toBeInserted;
                    toBeInserted->parent = ptr;
                    break;
                }
            }
            else if(ptr->key < toBeInserted->key)
            {
                if(ptr->right != nullptr)
                    ptr = ptr->right;
                else
                {
                    ptr->right = toBeInserted;
                    toBeInserted->parent = ptr;
                    break;
                }
            }
            else
            {
                cout << "The number " << toBeInserted->key << " is already in the tree." << endl << endl;
                break;
            }
        }
    }
}

void orderedPrint(Node * root)
{
    if(root != nullptr)
    {
        orderedPrint(root->left);
        cout << root->key << " ";
        orderedPrint(root->right);
    }
}

void printEdges(Node * root)
{
    if(root != nullptr)
    {
        if(root->left != nullptr)
        {
            cout << root->key << "->" << root->left->key << endl;
            printEdges(root->left);
        }
        if(root->right != nullptr)
        {
            cout << root->key << "->" << root->right->key << endl;
            printEdges(root->right);
        }
    }
}

int successor(Node *ptr)
{
    if(ptr->right == nullptr)
    {
        if(ptr->key < ptr->parent->key)
            return ptr->parent->key;
        else
        {
            Node *ptr2 = ptr;
            while(ptr2->key > ptr->parent->key)
                ptr = ptr->parent;
            return ptr->parent->key;
        }
    }
    else
    {
        ptr = ptr->right;
        while(ptr->left != nullptr)
            ptr = ptr->left;
        return ptr->key;
    }
}

int predecessor(Node *ptr)
{
    if(ptr->left == nullptr)
    {
        if(ptr->key > ptr->parent->key)
            return ptr->parent->key;
        else
        {
            Node *ptr2 = ptr;
            while(ptr2->key < ptr->parent->key)
                ptr = ptr->parent;
            return ptr->key;
        }
    }
    else
    {
        ptr = ptr->left;
        while(ptr->right != nullptr)
            ptr = ptr->right;
        return ptr->key;
    }
}

int main()
{
    int operation = 0, number;
    Node * root = nullptr;
    
    while(operation != 8)
    {
        cout << "Binary search tree – operations: " << endl << endl
        << "1) Insert a value" << endl
        << "2) Ordered print of keys" << endl
        << "3) Print of connections" << endl
        << "4) Search" << endl
        << "5) Print min/max" << endl
        << "6) Print successor and predecessor" << endl
        << "7) Remove a node" << endl
        << "8) End" << endl << endl
        << "Operation: ";
        cin >> operation;
        
        switch (operation) {
            case 1:
            {
                cout << endl << "Enter the number: ";
                cin >> number;
                Node *ptr = new Node(number);
                ptr->key = number;
                insertToTree(root,ptr);
                break;
            }
            case 2:
                cout << endl;
                orderedPrint(root);
                cout << endl << endl;
                break;
            case 3:
                printEdges(root);
                cout << endl;
                break;
            case 4:
            {
                cout << "Enter the number to be searched: ";
                cin >> number;
                Node *ptr = root;
                bool isExists = false;
                while(ptr != nullptr && !isExists)
                {
                    if(ptr->key > number)
                        ptr = ptr->left;
                    else if(ptr->key < number)
                        ptr = ptr->right;
                    else
                    {
                        cout << endl << "The number " << number << " exists." << endl << endl;
                        isExists = true;
                    }
                }
                if(!isExists)
                    cout << endl << "Not found." << endl << endl;
                break;
            }
            case 5:
            {
                Node *ptr = root;
                if(ptr != nullptr)
                {
                    while(ptr->left != nullptr)
                        ptr = ptr->left;
                    cout << endl << "Min: " << ptr->key << endl;
                    ptr = root;
                    while(ptr->right != nullptr)
                        ptr = ptr->right;
                    cout << endl << "Max: " << ptr->key << endl << endl;
                }else
                    cout << endl << "The tree is empty." << endl << endl;
                break;
            }
            case 6:
            {
                cout << "Enter the number: ";
                cin >> number;
                Node *ptr = root;
                bool isExists = false;
                while(ptr != nullptr && !isExists)
                {
                    if(ptr->key > number)
                        ptr = ptr->left;
                    else if(ptr->key < number)
                        ptr = ptr->right;
                    else
                        isExists = true;
                }
                if(!isExists)
                    cout << endl << "There is no " << number << endl << endl;
                else
                {
                    cout << endl << "Successor: " << successor(ptr) << endl;
        
                    cout << endl << "Predecessor: " << predecessor(ptr) << endl << endl;
                }
                break;
            }
            case 7:
            {
                cout << "Enter the number to be deleted: ";
                cin >> number;
                Node *ptr = root;
                bool isExists = false;
                while(ptr != nullptr && !isExists)
                {
                    if(ptr->key > number)
                        ptr = ptr->left;
                    else if(ptr->key < number)
                        ptr = ptr->right;
                    else
                        isExists = true;
                }
                if(!isExists)
                    cout << endl << "There is no " << number << endl << endl;
                
                //Case 1: Remove a leaf
                else{
                    if(ptr->left == nullptr && ptr->right == nullptr)
                    {
                        if(ptr->parent == nullptr)
                            root = nullptr;
                        else if(ptr->parent->left != nullptr && ptr->parent->left->key == number)
                            ptr->parent->left = nullptr;
                        else if(ptr->parent->right != nullptr && ptr->parent->right->key == number)
                            ptr->parent->right = nullptr;
                        delete ptr;
                    }
                    
                    //Case 2: Remove a node with one child
                    else if(ptr->left == nullptr)
                    {
                        if(ptr->parent != nullptr)
                        {
                            if(ptr->parent->left == ptr)
                            {
                                ptr->parent->left = ptr->right;
                                ptr->right->parent = ptr->parent;
                                delete ptr;
                            }
                            else
                            {
                                ptr->parent->right = ptr->right;
                                ptr->right->parent = ptr->parent;
                                delete ptr;
                            }
                        }
                        else
                        {
                            root = ptr->right;
                            root->parent = nullptr;
                            delete ptr;
                        }
                    }
                    else if(ptr->right == nullptr)
                    {
                        if(ptr->parent != nullptr)
                        {
                            if(ptr->parent->left == ptr)
                            {
                                ptr->parent->left = ptr->left;
                                ptr->left->parent = ptr->parent;
                                delete ptr;
                            }
                            else
                            {
                                ptr->parent->right = ptr->left;
                                ptr->left->parent = ptr->parent;
                                delete ptr;
                            }
                        }
                        else
                        {
                            root = ptr->left;
                            root->parent = nullptr;
                            delete ptr;
                        }
                    }

                    //Case 3: Remove a node with two child
                    else{
                        Node * successor = ptr;
                        successor = successor->right;
                        while(successor->left != nullptr)
                            successor = successor->left;
                        if(successor->parent != nullptr)
                        {
                            if(successor->parent->left == successor)
                            {
                                successor->parent->left = nullptr;
                                successor->parent->right->parent = successor;
                            }
                            else
                            {
                                successor->parent->right = nullptr;
                                successor->parent->left->parent = successor;
                            }
                        }
                        if(ptr->parent != nullptr)
                        {
                            if(ptr->parent->left == ptr)
                                ptr->parent->left = successor;
                            else
                                ptr->parent->right = successor;
                        }
                        successor->parent = ptr->parent;
                        successor->right = ptr->right;
                        successor->left = ptr->left;
                        if(ptr == root)
                            root = successor;
                        delete ptr;
                    }
                }
                break;
            }
            default:
                break;
        }
    }
    
    return 0;
}
