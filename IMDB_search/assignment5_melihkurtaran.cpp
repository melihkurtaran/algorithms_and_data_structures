//  Created by Melih Kurtaran on 22/03/2019.
//  Copyright © 2019 melihkurtaran. All rights reserved.

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

struct NodeOfLL //Node of linked list
{
    NodeOfLL(string movie, NodeOfLL* next)
    :movie(movie),next(next){};
    
    string movie;
    NodeOfLL *next;
};

struct NodeOfTree{
    NodeOfTree(int date): date(date){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        headOfMovies = nullptr;
    }
    
    int date;
    NodeOfTree* parent;
    NodeOfTree* left;
    NodeOfTree* right;
    NodeOfLL* headOfMovies;
};

void insertToTree(NodeOfTree * &root, int date, string movieName)
{
    if(root == nullptr)
    {
        root = new NodeOfTree(date);
        root->headOfMovies = new NodeOfLL(movieName,nullptr);
    }
    else
    {
        NodeOfTree *ptr = root, *prev = nullptr;
        NodeOfLL *ptr2;
        bool isAdded = false;
        while(ptr != nullptr && !isAdded)
        {
            prev = ptr;
            if(ptr->date > date)
                ptr = ptr->left;
            else if(ptr->date < date)
                ptr = ptr->right;
            else
            {
                ptr2 = ptr->headOfMovies;
                while(ptr2->next != nullptr)
                    ptr2 = ptr2->next;
                ptr2->next = new NodeOfLL(movieName,nullptr);
                isAdded = true;
            }
        }
        if(!isAdded)
        {
            ptr = new NodeOfTree(date);
            ptr->headOfMovies = new NodeOfLL(movieName,nullptr);
            if(prev->date > date)
                prev->left = ptr;
            else if(prev->date < date)
                prev->right = ptr;
            ptr->parent = prev;
        }
    }
}

void printMovies(NodeOfTree * root)
{
    NodeOfLL *ptr = nullptr;
    if(root != nullptr)
    {
        printMovies(root->left);
        ptr = root->headOfMovies;
        cout << "-- " << root->date << " --" << endl;
        while(ptr != nullptr)
        {
            cout << ptr->movie << endl;
            ptr = ptr->next;
        }
        printMovies(root->right);
    }
}

void printEdges(NodeOfTree * root)
{
    if(root != nullptr)
    {
        if(root->left != nullptr)
        {
            cout << root->date << "->" << root->left->date << endl;
            printEdges(root->left);
        }
        if(root->right != nullptr)
        {
            cout << root->date << "->" << root->right->date << endl;
            printEdges(root->right);
        }
    }
}

int successor(NodeOfTree *ptr)
{
    if(ptr->right == nullptr)
    {
        if(ptr->date < ptr->parent->date)
            return ptr->parent->date;
        else
        {
            NodeOfTree *ptr2 = ptr;
            while(ptr2->date > ptr->parent->date)
                ptr = ptr->parent;
            return ptr->parent->date;
        }
    }
    else
    {
        ptr = ptr->right;
        while(ptr->left != nullptr)
            ptr = ptr->left;
        return ptr->date;
    }
}

int predecessor(NodeOfTree *ptr)
{
    if(ptr->left == nullptr)
    {
        if(ptr->date > ptr->parent->date)
            return ptr->parent->date;
        else
        {
            NodeOfTree *ptr2 = ptr;
            while(ptr2->date < ptr->parent->date)
                ptr = ptr->parent;
            return ptr->date;
        }
    }
    else
    {
        ptr = ptr->left;
        while(ptr->right != nullptr)
            ptr = ptr->right;
        return ptr->date;
    }
}

void deleteMovies(NodeOfTree * &ptr)
{
    NodeOfLL* prev = ptr->headOfMovies;
    while(ptr->headOfMovies != nullptr)
    {
        ptr->headOfMovies = ptr->headOfMovies->next;
        delete prev;
        prev = ptr->headOfMovies;
    }
}

int main() {

    int operation = 0, date;
    string movieName;
    NodeOfTree *root = nullptr;
    while(operation != 9)
    {
        cout << endl << "Binary search tree – operations: " << endl
        << "1) Insert a movie "<< endl
        << "2) Print all movies"<< endl
        << "3) Print all connections"<< endl
        << "4) Find movies from specific date"<< endl
        << "5) Print minimum and maximum date"<< endl
        << "6) Print successor and predecessor"<< endl
        << "7) Remove all movies at specific date"<< endl
        << "8) Load movies from file"<< endl << endl
        << "9) End"<< endl << endl
        << "Operation:";
        cin >> operation;
        
        switch (operation) {
            case 1:
                cout << endl << "Enter the date: ";
                cin >> date;
                cout << endl << "Enter the name of movie: ";
                cin >> movieName;
                insertToTree(root, date, movieName);
                break;
            case 2:
                printMovies(root);
                break;
            case 3:
                printEdges(root);
                break;
            case 4:
            {
                cout << "Enter the date: ";
                cin >> date;
                auto start = chrono::steady_clock::now();
                NodeOfTree *ptr = root;
                NodeOfLL *ptr2 = nullptr;
                bool isExists = false;
                while(ptr != nullptr && !isExists)
                {
                    if(ptr->date > date)
                        ptr = ptr->left;
                    else if(ptr->date < date)
                        ptr = ptr->right;
                    else
                    {
                        ptr2 = ptr->headOfMovies;
                        cout << endl;
                        isExists = true;
                    }
                    while(ptr2 != nullptr)
                    {
                        ptr2 = ptr2->next;
                    }
                }
                auto end = chrono::steady_clock::now();
                cout << "Total time: " <<
                chrono::duration_cast<std::chrono::microseconds>(end - start).count() <<
                "μs."<< endl << endl;
                if(!isExists)
                    cout << endl << "Not found." << endl << endl;
                break;
            }
            case 5:
            {
                NodeOfTree *ptr = root;
                if(ptr != nullptr)
                {
                    while(ptr->left != nullptr)
                        ptr = ptr->left;
                    cout << endl << "Min: " << ptr->date << endl;
                    ptr = root;
                    while(ptr->right != nullptr)
                        ptr = ptr->right;
                    cout << endl << "Max: " << ptr->date << endl;
                }else
                    cout << endl << "The tree is empty." << endl << endl;
                break;
            }
            case 6:
            {
                cout << "Enter the date: ";
                cin >> date;
                NodeOfTree *ptr = root;
                bool isExists = false;
                while(ptr != nullptr && !isExists)
                {
                    if(ptr->date > date)
                        ptr = ptr->left;
                    else if(ptr->date < date)
                        ptr = ptr->right;
                    else
                        isExists = true;
                }
                if(!isExists)
                    cout << endl << "There is no " << date << endl << endl;
                else
                {
                    cout << endl << "Successor: " << successor(ptr) << endl;
                   
                    cout << endl << "Predecessor: " << predecessor(ptr) << endl << endl;
                }
                break;
            }
            case 7:
            {
                cout << "Enter the date to be deleted: ";
                cin >> date;
                NodeOfTree *ptr = root;
                bool isExists = false;
                while(ptr != nullptr && !isExists)
                {
                    if(ptr->date > date)
                        ptr = ptr->left;
                    else if(ptr->date < date)
                        ptr = ptr->right;
                    else
                        isExists = true;
                }
                if(!isExists)
                    cout << endl << "There is no date " << date << endl << endl;
                
                //Case 1: Remove a leaf
                else{
                    if(ptr->left == nullptr && ptr->right == nullptr)
                    {
                        if(ptr->parent == nullptr)
                            root = nullptr;
                        else if(ptr->parent->left != nullptr && ptr->parent->left->date == date)
                            ptr->parent->left = nullptr;
                        else if(ptr->parent->right != nullptr && ptr->parent->right->date == date)
                            ptr->parent->right = nullptr;
                        deleteMovies(ptr);
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
                                deleteMovies(ptr);
                                delete ptr;
                            }
                            else
                            {
                                ptr->parent->right = ptr->right;
                                ptr->right->parent = ptr->parent;
                                deleteMovies(ptr);
                                delete ptr;
                            }
                        }
                        else
                        {
                            root = ptr->right;
                            root->parent = nullptr;
                            deleteMovies(ptr);
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
                                deleteMovies(ptr);
                                delete ptr;
                            }
                        }
                        else
                        {
                            root = ptr->left;
                            root->parent = nullptr;
                            deleteMovies(ptr);
                            delete ptr;
                        }
                    }
                    
                    //Case 3: Remove a node with two child
                    else{
                        NodeOfTree * successor = ptr;
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
                        deleteMovies(ptr);
                        delete ptr;
                    }
                }
                break;
            }
            case 8:
            {
                string fileName;
                ifstream input;
                cout << "Enter the name of file: ";
                cin >> fileName;
                input.open(fileName.c_str());
                while(!input.is_open())
                {
                    cout << "File could not be opened." << endl
                    << "Enter the name of file: ";
                    cin >> fileName;
                    input.open(fileName.c_str());
                }
                long long N;
                string name;
                input >> N;
                for(long long i=0; i<N; i++)
                {
                    input >> date;
                    getline(input, name, '\n');
                    insertToTree(root, date, name);
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
