#include <bits/stdc++.h>
#include <vector>
#include "node.h"
#include "algorithm.h"

using namespace std;
// answer: 1 2 3 4 5 6 7 8 9 0 0 0 0
//vector<int> test = {1, 0, 0, 0, 2, 3, 4, 6, 7, 9, 0, 5, 8}; // medium problem step 13 // depth 14 
//vector<int> test = {1, 2, 3, 4, 5, 0, 0, 6, 7, 9, 0, 0, 8}; // depth 6 step 24 easy 
//vector<int> test = {1, 2, 3, 0, 5, 0, 7, 0, 9, 0, 4, 6, 8}; // depth 4 easy 
//vector<int> test = {1, 2, 3, 0, 5, 6, 7, 8, 9, 0, 4, 0, 0}; // should give depth of 1 // easy problem 
//vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0};

int main(){

    cout << "Welcome to Nine Men in a Trench puzzle solver!" << endl;
    cout << "Type 1 for uniform cost search, 2 for Misplaced Tiles and 3 for Manhattan distance" << endl;

    int h = 0;

    cin >> h;

    cout << "Type the trench state one by one all the way including the recess part with space separated" << endl;
    cout << "Ex: 1 2 3 4 5 6 7 8 9 0 0 0 0 The last 3 numbers are for recesses" << endl; 
    vector<int> trench;
    int val;
    for (int i = 0; i < 13; i++) {
        cin >> val;
        trench.push_back(val);
    }

    Node* input = new Node(trench, 0, 0, nullptr, 0);
    Algorithm a = Algorithm();
    
    a.setHeuristic(h);
    Node* ans = a.solve(input);
    
    while(ans->getParent() != nullptr){
        //prints the vector
        cout << "Trench: " << ans->printTrench() << endl;
        cout << "g(n) = " << ans->getGn() << endl;
        cout << "h(n) = " << ans->getHn() << endl;
        ans = ans->getParent();
        cout << endl;
    }
    

    return 0;
}