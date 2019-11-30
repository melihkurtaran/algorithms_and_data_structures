//  Created by Melih Kurtaran on 27/02/2019.
//  Copyright © 2019 melihkurtaran. All rights reserved.

#include <iostream>

using namespace std;

int main()
{
    int selection = 0, MAX;
    cout << "Please, specify the maximum number of elements: ";
    cin >> MAX;
    
    int S[MAX], Q[MAX];
    int toBeInserted, toBePopped, topStack = -1;
    int headOfQueue = 0, tailOfQueue = 0;
    int number;
    
    while(selection != 7)
    {
        cout << endl << "Stack – selection: " << endl
        << "1) Insert a number "<< endl
        << "2) Read a number " << endl
        << "3) Print the stack " << endl
        << "Queue – selection: " << endl
        << "4) Insert a number " << endl
        << "5) Read a number " << endl
        << "6) Print the queue from head to tail " << endl
        << "7) Exit" << endl;
        
        cout << "Selection: ";
        cin >> selection;
        
        switch (selection) {
            case 1:
                cout << "insert a number: ";
                cin >> toBeInserted;
                if(topStack != MAX-1)
                {
                    topStack++;
                    cout << endl << toBeInserted << " is inserted." << endl;
                    S[topStack] = toBeInserted;
                }
                else
                    cout << endl << "the stack is full. " << endl;
                break;
            case 2:
                if(topStack != -1)
                {
                    toBePopped = S[topStack];
                    topStack--;
                    cout << endl << toBePopped << " is deleted." << endl;
                }
                else
                    cout << endl << "the stack is empty. " << endl;
                break;
            case 3:
                if(topStack == -1)
                {
                    cout << endl << "the stack is empty. " << endl;
                }
                else
                {
                    cout << endl << "Stack: ";
                    for(int i=0; i <= topStack; i++)
                    {
                        cout << S[i] << " ";
                    }
                    cout << endl;
                }
                break;
            case 4:
                cout << "insert a number: ";
                cin >> toBeInserted;
                if(headOfQueue != tailOfQueue + 1)
                {
                    Q[tailOfQueue] = toBeInserted;
                    cout << endl << toBeInserted << " is inserted." << endl;
                    tailOfQueue = (tailOfQueue + 1) % MAX;
                }
                else
                    cout << endl << "The queue is full." << endl;
                
                break;
            case 5:
                if(headOfQueue != tailOfQueue)
                {
                    cout << endl << Q[headOfQueue] << " is deleted." << endl;
                    headOfQueue++;
                }
                else
                    cout << endl << "The queue is empty." << endl;
                break;
            case 6:
                if(headOfQueue == tailOfQueue)
                {
                    cout << endl << "The queue is empty." << endl;
                }
                else
                {
                    cout << endl << "The circular queue: ";
                    number = headOfQueue;
                    while(number != tailOfQueue)
                    {
                        cout << Q[number] << " ";
                        number++;
                    }
                    cout << endl;
                }
                break;
            case 7:
                cout << "Exiting.. " << endl;;
                break;
            default:
                cout << endl << "invalid selection" << endl;
                break;
        }
        
    }
    return 0;
}
