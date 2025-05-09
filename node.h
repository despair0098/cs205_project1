#ifndef NODE_H
#define NODE_H
#include <vector>

using namespace std;

class Node{
    public:
    vector<int> trench;
    int gn; // Cost from start node
    int hn; // Heuristic cost to goal
    int fn; // Total cost (g + h)
    Node* parent;
    int depth;

    Node(vector<int> t, int g, int h, Node* p, int d){
        trench = t;
        gn = g;
        hn = h;
        fn = g + h;
        parent = p;
        depth = d;
    }
    // Creates a node that contains the goal state
    Node(){
        depth = 0;
        trench.resize(14);
        // answer: 1 2 3 4 5 6 7 8 9 0 0 0 0
        for(int i = 0; i < 13; i++){
            if(i < 9){
                trench[i] = i+1;
            } else {
                trench[i] = 0;
            }
        }
    }

    void setTrench(vector<int> t){
        for(int i = 0; i < 14; i++){
            trench[i] = t[i];
        }
    }

    vector<int> getTrench(){
        return trench;
    }
    void setGn(int g){
        gn = g;
    }

    int getGn(){
        return gn;
    }

    void setHn(int h){
        hn = h;
    }

    int getHn(){
        return hn;
    }

    void setFn(int f){
        fn = f;
    }

    int getFn(){
        return fn;
    }

    Node* getParent(){
        return parent;
    }

    void setParent(Node* p){
        parent = p;
    }

    int getDepth(){
        return depth;
    }

    void setDepth(int d){
        depth = d;
    }
    // Finds the empty spaces inside the trench and return a vector of the index of them. 
    vector<int> findEmpty(){
        vector<int> indexes;
        for(int i = 0; i < 10; i++){
            if(trench[i] == 0){
                indexes.push_back(i);
            }
        }
        return indexes;
    }
    // Finds the empty spaces inside the recess and return a vector of the index of them.
    vector<int> findEmptyRecess(){
        vector<int> indexes;
        for(int i = 10; i < 13; i++){
            if(trench[i] == 0){
                indexes.push_back(i);
            }
        }
        return indexes;
    }
    //Compares the nodes to see if they are identical or not. 
    bool compareNodes(Node* a){
        vector<int> t = a->getTrench();
        for(int i = 0; i < 13; i++){
            if(t[i] != trench[i]){
                return false;
            }
        }
        return true;
    }
    //Checks to see if the node is a goal state
    bool isGoal(){
        // answer: 1 2 3 4 5 6 7 8 9 0 0 0 0
        for(int i = 0; i < 13; i++){
            if(i < 9){
                if(trench[i] != i+1){
                    return false;
                }
            } else {
                if(trench[i] != 0){
                    return false;
                }
            }
        }
        return true;
    }
    //Prints out the trench in string
    string printTrench(){
        string t = "";
        for(int i = 0; i < 13; i++){
            t += to_string(trench[i]);
            t += " ";
        }
        return t;
    }

};

#endif