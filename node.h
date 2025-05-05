#ifndef NODE_H
#define NODE_H
#include <vector>

using namespace std;

class Node{
    public:
    vector<int> trench;
    vector<int> recesses;
    int gn; // Cost from start node
    int hn; // Heuristic cost to goal
    int fn; // Total cost (g + h)
    Node* parent;
    int depth;

    Node(vector<int> t, int g, int h, Node* p, int d){
        trench = t;
        //recesses = r;
        gn = g;
        hn = h;
        fn = g + h;
        parent = p;
        depth = d;
    }

    Node(){
        depth = 0;
        for(int i = 0; i < 9; i++){
            if(i < 9){
                trench[i] = i+1;
            } else {
                trench[i] = 0;
            }
        }
    }

    void setTrench(vector<int> t){
        for(int i = 0; i < 13; i++){
            trench[i] = t[i];
        }
    }

    vector<int> getTrench(){
        return trench;
    }
    /*
    void setRecesses(vector<int> r){
        for(int i = 0; i < 3; i++){
            recesses[i] = r[i];
        }
    }

    vector<int> getRecesses(){
        return recesses;
    }
    */
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

    int setDepth(int d){
        depth = d;
    }
    // input is the soldier's number so 1 is the sergent and 2-9 are the soldier. 
    int findPosition(int num){
        for(int i = 0; i < 13; i++){
            if(trench[i] == num){
                return i+1;
            }
        }
        return 0;
    }

    vector<int> findEmpty(){
        vector<int> indexes;
        for(int i = 0; i < 9; i++){
            if(trench[i] == 0){
                indexes.push_back(i);
            }
        }
        return indexes;
    }

    vector<int> findEmptyRecess(){
        vector<int> indexes;
        for(int i = 10; i < 13; i++){
            if(trench[i] == 0){
                indexes.push_back(i);
            }
        }
        return indexes;
    }

    bool compareNodes(Node a){
        vector<int> t = a.getTrench();
        for(int i = 0; i < 13; i++){
            if(t[i] != trench[i]){
                return false;
            }
        }
        return true;
    }

    bool isGoal(){
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

};

#endif