#include <bits/stdc++.h>
#include "node.h"
#include "algorithm.h"
#include <vector>

using namespace std;
// answer: 1 2 3 4 5 6 7 8 9 0 0 0 0
//vector<int> test = {0, 2, 3, 4, 5, 6, 7, 8, 9, 1, 0 , 0, 0};
vector<int> test = {2, 1, 3, 4, 5, 6, 7, 8, 9, 0, 0 , 0, 0}; // should give depth of 1

int main(){

    cout << "Hello" << endl;
    Node* input = new Node(test, 0, 0, nullptr, 0);
    cout << "Hello2" << endl;
    Algorithm a = Algorithm();
    cout << "Hello3" << endl;
    Node* ans = a.solve(input);
    cout << "Hello4" << endl;
    vector<int> trench = ans->getTrench();
    for(int i = 0; i < trench.size(); i++){
        cout << trench[i] << " ";
    }
    /*
    while(ans->getParent() != nullptr){
        //prints the vector
        vector<int> trench = ans->getTrench();
        for(int i = 0; i < trench.size(); i++){
            cout << trench[i] << " ";
        }
        cout << "g(n) = " << ans->getGn() << endl;
        cout << "h(n) = " << ans->getHn() << endl;
        ans = ans->getParent();
        cout << endl;
    }
    */
    

    cout << "Hello" << endl;

    return 0;
}