//  Created by Melih Kurtaran on 15/05/2019.
//  Copyright © 2019 melihkurtaran. All rights reserved.

#include <iostream>
#include <fstream>
#include <random>
using namespace std;

struct Node {
    int predecessor;
    int price;
};

void BELLMAN_FORD(Node *G, int s, int size, int **C)
{
    for(int i=1; i < size; i++)
    {
        if(i==s)
            G[i].price = 0;
        else
            G[i].price = 9999;
        G[i].predecessor = -1;
    }
    for(int i=1; i < size; i++)
    {
        for(int r=1; r < size; r++)
        {
            for(int c=1; c < size; c++)
            {
                if(G[r].price + C[r][c] < G[c].price)
                {
                    G[c].price = G[r].price + C[r][c];
                    G[c].predecessor = r;
                }
            }
        }
    }
    for(int r=1; r < size; r++)
    {
        for(int c=1; c < size; c++)
        {
            if(G[r].price + C[r][c] < G[c].price)
            {
                cout << "ERROR!" << endl;
                return;
            }
        }
    }
}

void print(Node *G, int s,int v, int size, int **C,int price)
{
    if(v != s)
    {
        if(G[v].predecessor == -1)
            cout << "There is no path from " << s << " to " << v << endl;
        else
        {
            print(G,s,G[v].predecessor,size,C,price);
            cout << v << " ";
        }
    }
    else
    {
        cout << "Price of path is " << price << endl << endl;
        cout << "Path is " << v << " ";
    }
}

int main() {
    Node * G = nullptr;
    int operation = 0,s=1,v;
    int numberOfNodes = 0;
    int ** C = nullptr;
    while(operation != 5)
    {
        cout << "Bellman-Ford algorithm - operation: " << endl << endl
        << "1) Read a graph from a file "<< endl
        << "2) Generate random graph "<< endl
        << "3) Run Bellman-Ford (from node s) "<< endl
        << "4) Print cheapest path to node d "<< endl
        << "5) Exit " << endl << endl
        << "Your selection: ";
        cin >> operation;
        
        switch (operation) {
            case 1:
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
                input >> numberOfNodes;
                C = new int*[numberOfNodes+1];
                for(int i=0; i < numberOfNodes + 1; i++)
                    C[i] = new int[numberOfNodes+1];
                for(int r=1; r < numberOfNodes+1; r++)
                {
                    for(int c=1; c < numberOfNodes+1; c++)
                        input >> C[r][c];
                }
                break;
            }
            case 2:
            {
                cout << endl << "Please enter the number of nodes: ";
                cin >> numberOfNodes;
                C = new int*[numberOfNodes+1];
                for(int i=0; i < numberOfNodes+1; i++)
                    C[i] = new int[numberOfNodes+1];
                mt19937 rng;
                uniform_int_distribution<uint32_t> uint_dist(1,15);
                for(int r=1; r < numberOfNodes+1; r++)
                {
                    for(int c=1; c < numberOfNodes+1; c++)
                    {
                        if(r == c)
                            C[r][c]= 0;
                        else
                            C[r][c]= uint_dist(rng);
                    }
                }
                break;
            }
            case 3:
                cout << "Enter starting node: ";
                cin >> s;
                G = new Node[numberOfNodes+1];
                BELLMAN_FORD(G,s,numberOfNodes+1,C);
                break;
            case 4:
                cout << "Enter the ending node: ";
                cin >> v;
                cout << endl;
                print(G,s,v,numberOfNodes+1,C,G[v].price);
                cout << endl << endl;
                break;
            default:
                break;
        }
    }
    for(int i=0; i < numberOfNodes+1; i++)
        delete [] C[i];
    return 0;
}
