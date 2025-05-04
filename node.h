#ifndef NODE_H
#define NODE_H
#include <vector>

using namespace std;

class Node{
    public:
    vector<int> trench; // 11 12 13 are the recesses 11 is on top of 4, 12 is on 6, and 13 on 8
    //vector<int> recesses;
    int gn; // Cost from start node
    int hn; // Heuristic cost to goal
    int fn; // Total cost (g + h)
    Node* parent;
    int depth;

    Node(vector<int> t, int g, int h, int f, Node* p, int d){
        trench = t;
        //recesses = r;
        gn = g;
        hn = h;
        fn = f;
        parent = p;
        depth = d;
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