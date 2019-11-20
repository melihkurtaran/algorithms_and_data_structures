//  Created by Melih Kurtaran on 27/03/2019.
//  Copyright © 2019 melihkurtaran. All rights reserved.

#include <iostream>
#include <chrono>
#include <random>

using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;
using namespace std;

void isSorted(int *array, int size)
{
    bool isSorted = true;
    for(int i=0;i<size-1;i++)
    {
        if(array[i+1] < array[i])
        {
            cout <<"The array is NOT sorted."<< endl << endl;
            isSorted = false;
            break;
        }
    }
    if(isSorted)
        cout <<"The array is sorted."<< endl << endl;
}

int partition(int *array, int firstIndex, int lastIndex, string name)
{
    int temp;
    int pe; //pivot
    
    if(name=="quick")
        pe = array[firstIndex];
    else if(name=="median")
    {
        pe = array[firstIndex + (lastIndex-firstIndex)/2];
        temp = array[firstIndex];
        array[firstIndex] = pe;
        array[firstIndex + (lastIndex-firstIndex)/2] = temp;
    }
    else //randomized quick sort
    {
        mt19937 rng;
        uniform_int_distribution<uint32_t> uint_dist(firstIndex,lastIndex);
        int random = uint_dist(rng);
        pe = array[random];
        temp = array[firstIndex];
        array[firstIndex] = pe;
        array[random] = temp;
    }
    int l = firstIndex;
    int r = lastIndex;
    while(l<r)
    {
        while(array[l] <= pe && l < lastIndex)
            l++;
        while(array[r] >= pe && r > firstIndex)
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

void quickSort(int *array, int firstIndex, int lastIndex)
{
    int j;
    if(firstIndex < lastIndex)
    {
        j = partition(array,firstIndex,lastIndex,"quick");
        quickSort(array,firstIndex,j-1);
        quickSort(array,j+1,lastIndex);
    }
}

void randomSeq(int *array, int size)
{
    mt19937 rng;
    uniform_int_distribution<uint32_t> uint_dist(1,size);
    for(int i=0;i<size;i++)
    {
        array[i] = uint_dist(rng);
    }
}

void printSeq(int *array, int size)
{
    cout << endl;
    for(int i=0;i<size;i++)
    {
        cout << array[i] << " ";
    }
    cout << endl << endl;
}

void increasingSeq(int *array, int size)
{
    for(int i=0;i<size;i++)
    {
        array[i] = i + 1;
    }
}

void decreasingSeq(int *array, int size)
{
    for(int i=0;i<size;i++)
    {
        array[i] = size-i;
    }
}

void medianSort(int *array, int firstIndex, int lastIndex)
{
    int j;
    if(firstIndex < lastIndex)
    {
        j = partition(array,firstIndex,lastIndex,"median");
        medianSort(array,firstIndex,j-1);
        medianSort(array,j+1,lastIndex);
    }
}

void selectionSort(int *array,int size)
{
    int minIndex, temp;
    for(int i=0; i<size; i++)
    {
        minIndex = i;
        for(int j = i+1; j<size+1;j++)
        {
            if(array[j] < array[minIndex])
                minIndex = j;
        }
        if(minIndex != i)
        {
            temp = array[i];
            array[i] = array[minIndex];
            array[minIndex] = temp;
        }
    }
}

int main()
{
    int operation = 0, size;
    cout << "Enter the size of sequence: ";
    cin >> size;
    int *array = new int[size];
    while(operation != 9)
    {
        cout << "Quicksort – operation:" << endl
        << "1) Generate random sequence"<< endl
        << "2) Generate increasing sequence"<< endl
        << "3) Generate decreasing sequence"<< endl
        << "4) Print current sequence"<< endl
        << "5) Check if array is sorted"<< endl
        << "6) Sort with Quicksort"<< endl
        << "7) Sort with randomized or median Quicksort"<< endl
        << "8) Sort with any other algorithm(selection)"<< endl
        << "9) End"<< endl
        << "10) Compare the sort algorithms" << endl << endl
        << "Operation: ";
        cin >> operation;
        
        switch (operation) {
            case 1:
                randomSeq(array,size);
                cout << endl << "Random sequence is generated." << endl << endl;
                break;
            case 2:
                increasingSeq(array,size);
                cout << endl << "Increasing sequence is generated." << endl << endl;
                break;
            case 3:
                decreasingSeq(array,size);
                cout << endl << "Decreasing sequence is generated." << endl << endl;
                break;
            case 4:
                printSeq(array,size);
                break;
            case 5:
                isSorted(array,size);
                break;
            case 6:
                quickSort(array,0,size-1);
                cout << endl << "Quick sort is done." << endl << endl;
                break;
            case 7:
                medianSort(array,0,size-1);
                cout << endl << "Median sort is done." << endl << endl;
                break;
            case 8:
                selectionSort(array,size);
                cout << endl << "Selection sort is done." << endl << endl;
                break;
            case 10:
            {
                steady_clock::time_point start = steady_clock::now();
                quickSort(array,0,size-1);
                steady_clock::time_point end = steady_clock::now();
                std::cout << "Duration of quicksort: "<<
                duration_cast<microseconds>(end - start).count() << "µs" << endl;
                
                steady_clock::time_point start2 = steady_clock::now();
                medianSort(array,0,size-1);
                steady_clock::time_point end2 = steady_clock::now();
                std::cout << "Duration of median quicksort: "<<
                duration_cast<microseconds>(end2 - start2).count() << "µs" << endl;
                
                steady_clock::time_point start3 = steady_clock::now();
                selectionSort(array,size);
                steady_clock::time_point end3 = steady_clock::now();
                std::cout << "Duration of selection sort: "<<
                duration_cast<microseconds>(end3 - start3).count() << "µs" << endl << endl;
            }
            default:
                break;
        }
    }
    delete [] array;
    return 0;
}
