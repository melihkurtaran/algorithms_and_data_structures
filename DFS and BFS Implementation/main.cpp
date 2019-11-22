//  Created by Melih Kurtaran on 17/04/2019.
//  Copyright © 2019 melihkurtaran. All rights reserved.

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <chrono>

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;
using namespace std;

struct Vertex {
    int d; //distance
    Vertex * π;
    string color;
    int index;
};

void BFS(Vertex *G,int **C, int s, int nv)
{
    queue<int> queue;
    G[s].color = "gray";
    G[s].π = nullptr;
    G[s].d = 0;
    while(G[s].color == "gray")
    {
        for(int i=1; i<=nv;i++)
        {
            if(C[s][i] && G[i].color == "white")
            {
                G[i].color = "gray";
                G[i].π = &G[s];
                queue.push(G[i].index);
                G[i].d = G[s].d + 1;
            }
        }
        G[s].color = "black";
        if(!queue.empty())
        {
            s = queue.front();
            queue.pop();
        }
    }
}

void DFS(Vertex *G,int **C, int s, int nv)
{
    stack<int> stack;
    G[s].color = "gray";
    G[s].π = nullptr;
    G[s].d = 0;
    while(G[s].color == "gray")
    {
        for(int i=1; i<=nv;i++)
        {
            if(C[s][i] && G[i].color == "white")
            {
                G[i].color = "gray";
                G[i].π = &G[s];
                stack.push(G[i].index);
                G[i].d = G[s].d + 1;
            }
        }
        G[s].color = "black";
        if(!stack.empty())
        {
            s = stack.top();
            stack.pop();
        }
    }
}

void printPath(Vertex *G, Vertex *s, Vertex *v)
{
    if(v->index == s->index)
        cout << s->index << " ";
    else if(v->π == nullptr)
        cout << "There is no path from " << s->index << " to " << v->index << " exists." << endl << endl;
    else
    {
        printPath(G,s,v->π);
        cout << v->index << " ";
    }
}

int main() {
    
    int operation = 0;
    Vertex *G = nullptr;
    int **C = nullptr;
    int nv = 0,ne = 0; //number of verticles and edges
    
    while(operation != 4)
    {
        cout << "Depth-first search and breadth-first search: " << endl << endl
        << "1) Read a graph.txt"<< endl
        << "2) Breadth-first search from s to d"<< endl
        << "3) Depth-first search from s to d"<< endl
        << "4) Exit"<< endl << endl
        << "Operation: ";
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
                input >> nv >> ne;
                G = new Vertex[nv+1];
                C = new int*[nv+1];
                for(int i=0;i<=nv;i++)
                {
                    C[i] = new int[nv+1];
                }
                for(int i=0;i <= nv;i++)
                {
                    for(int j=0;j<= nv;j++)
                    {
                        C[i][j] = 0;
                    }
                }
                int a,b,exist;
                for(int i=0;i<ne;i++)
                {
                    input >> a >> b >> exist;
                    if(exist)
                    {
                        C[a][b] = 1;
                        C[b][a] = 1;
                    }
                }
                break;
            }
            case 2:
            {
                for(int i=1;i<nv+1;i++)
                {
                    G[i].index = i;
                    G[i].color = "white";
                    G[i].d = 0;
                }
                int s,d;
                cout << endl << "Enter source: ";
                cin >> s;
                cout << endl << "Enter destination: ";
                cin >> d;
                if(G==nullptr||C==nullptr||nv==0)
                    cout << endl << "Please, read a graph first!" << endl;
                else
                {
                    BFS(G,C,s,nv);
                    steady_clock::time_point start = steady_clock::now();
                    printPath(G,&G[s],&G[d]);
                    steady_clock::time_point end = steady_clock::now();
                    cout << endl << "Distance: " << G[d].d << endl;
                    std::cout << "Duration of breadth-first search: "<<
                    duration_cast<microseconds>(end - start).count() << "µs" << endl;
                    cout << endl << endl;
                }
                break;
            }
            case 3:
            {
                for(int i=1;i<nv+1;i++)
                {
                    G[i].index = i;
                    G[i].color = "white";
                    G[i].d = 0;
                }
                int s,d;
                cout << endl << "Enter source: ";
                cin >> s;
                cout << endl << "Enter destination: ";
                cin >> d;
                if(G==nullptr||C==nullptr||nv==0)
                    cout << endl << "Please, read a graph first!" << endl;
                else
                {
                    DFS(G,C,s,nv);
                    steady_clock::time_point start = steady_clock::now();
                    printPath(G,&G[s],&G[d]);
                    steady_clock::time_point end = steady_clock::now();
                    cout << endl << "Distance: " << G[d].d << endl;
                    std::cout << "Duration of depth-first search: "<<
                    duration_cast<microseconds>(end - start).count() << "µs" << endl;
                    cout << endl << endl;
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
}
