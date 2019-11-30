//  Created by Melih Kurtaran on 08/05/2019.
//  Copyright © 2019 melihkurtaran. All rights reserved.

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;
using namespace std;

struct edge {
    int p;
    int q;
    int w; //weight
};

int findMax(int set[], int size)
{
    int max = 0 ;
    for(int i=1; i < size;i++)
    {
        if(set[i] > max)
            max = set[i];
    }
    return max;
}

int partition(edge *array, int firstIndex, int lastIndex)
{
    edge temp;
    int pe = array[firstIndex].w;
    int l = firstIndex;
    int r = lastIndex;
    while(l<r)
    {
        while(array[l].w <= pe && l < lastIndex)
            l++;
        while(array[r].w >= pe && r > firstIndex)
            r--;
        if(l < r)
        {
            temp = array[l];
            array[l] = array[r];
            array[r] = temp;
        }
    }
    temp = array[firstIndex];
    array[firstIndex] = array[r];
    array[r] = temp;
    return r;
}

void sort_edges_by_weight(edge *array, int firstIndex, int lastIndex)
{
    int j;
    if(firstIndex < lastIndex)
    {
        j = partition(array,firstIndex,lastIndex);
        sort_edges_by_weight(array,firstIndex,j-1);
        sort_edges_by_weight(array,j+1,lastIndex);
    }
}

edge * KRUKSAL(edge *P, int ne,int nv)
{
    edge * result = new edge[nv-1];
    sort_edges_by_weight(P,0,ne);
    int set[nv+1], k = 0;
    for(int i=0; i < nv+1; i++)
        set[i] = 0;
    for(int i=0; i <= ne; i++)
    {
        int p = P[i].p;
        int q = P[i].q;
        int w = P[i].w;
        if(p>nv || p<1 || q>nv || q<1)
            continue;
        if(set[p] == 0 && set[q] == 0)
        {
            set[p] = findMax(set,nv+1) + 1;
            set[q] = set[p];
            result[k].p = p;
            result[k].q = q;
            result[k++].w = w;
        }
        else if((set[p] != set[q]) && set[p] != 0 && set[q] != 0)
        {
            int temp = set[p];
            for(int i=1; i < nv+1;i++)
            {
                if(set[i] == temp)
                    set[i] = set[q];
            }
            result[k].p = p;
            result[k].q = q;
            result[k++].w = w;
        }
        else if(set[p] != 0 && set[q] == 0)
        {
            set[q] = set[p];
            result[k].p = p;
            result[k].q = q;
            result[k++].w = w;
        }
        else if(set[q] != 0 && set[p] == 0)
        {
            set[p] = set[q];
            result[k].p = p;
            result[k].q = q;
            result[k++].w = w;
        }
        if(k == nv-1)
            return result;
    }
    cout << "No solution." << endl << endl;
    return result;
}

int main()
{
    int operation = 0;
    int nv = 0,ne = 0; //number of verticles and edges
    edge *edges = nullptr;
    edge *result = nullptr;
    
    while(operation != 5)
    {
        cout << "Kruskal algorithm – selection: " << endl << endl
        << "1| Read graph from file "<< endl
        << "2| Generate random graph "<< endl
        << "3| Run "<< endl
        << "4| Output accepted edges "<< endl
        << "5| End"<< endl << endl
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
                input >> nv >> ne;
                edges = new edge[ne];
                int a,b,weight;
                for(int i=1;i<=ne;i++)
                {
                    input >> a >> b >> weight;
                    edges[i].p = a;
                    edges[i].q = b;
                    edges[i].w = weight;
                }
                break;
            }
            case 2:
            {
                cout << endl << "Please enter the number of vertex: ";
                cin >> nv;
                while(nv < 2)
                {
                    cout << endl << "Number of vertex cannot be smaller than 2!" << endl;
                    cout << endl << "Please enter the number of vertex again: ";
                    cin >> nv;
                }
                ne = nv*(nv-1)/2;
                edges = new edge[ne];
                int k=1;
                mt19937 rng;
                uniform_int_distribution<uint32_t> uint_dist(1,100);
                for(int i=1;i<=nv;i++)
                {
                    for(int j=i+1;j<=nv;j++)
                    {
                        edges[k].p = i;
                        edges[k].q = j;
                        edges[k].w = uint_dist(rng);
                        k++;
                    }
                }
                break;
            }
            case 3:
            {
                steady_clock::time_point start = steady_clock::now();
                result = KRUKSAL(edges,ne,nv);
                steady_clock::time_point end = steady_clock::now();
                cout << endl;
                cout << "Duration of kruksal algorithm: "<<
                duration_cast<microseconds>(end - start).count() << "µs" << endl;
                cout << endl;
                break;
            }
            case 4:
                for(int i=0;i<nv-1;i++)
                {
                    cout << "From node " << result[i].p << " to node " << result[i].q;
                    cout << " weight is " << result[i].w << " " << endl;
                }
                cout << endl << endl;
                break;
            default:
                break;
        }
    }
    delete [] edges;
    delete [] result;
    return 0;
}
