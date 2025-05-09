#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <iostream>
#include <vector>
#include <cmath> 
#include "node.h"

using namespace std;

class Algorithm {
private:
 
 //queue of nodes to visit, ordered in rank of heuristic
  vector<Node*> queue;
  vector<Node*> visited;   // nodes that are already visited (vector)
  Node goal = Node(); // goal state being 1 2 3 4 5 6 7 8 9 0 for 10 trench tiles and 0 0 0 for recesses
  int heuristic;

public:


  Algorithm(){
    heuristic = 1; // default being UCS
  }

  void setHeuristic(int h){
    heuristic = h;
  }

  //general_search(problem, QUEUEING-FUNCTION){
  Node* solve(Node* input){
    int nodesTraversed = 0;
    int queueSize = 0;

    //nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
      queue.push_back(input);
      //cout << "Popping" << endl;

      //loop do 
      while(queue.size() > 0){ // adding timer condition
      //for(int i = 0; i < 2; i++){
        // node = REMOVE-FRONT(nodes) 
        //for(int i = 0; i < queue.size(); i++){
        //  cout << queue[i]->printTrench() << endl;
        //  cout << "F(n)" << queue[i]->getFn() << endl;
        //} 
        Node* current = queue[queue.size()-1];
        //cout << "Current node: " << current->printTrench() << endl;
        queue.pop_back();
        //vector<Node*>::iterator it = queue.begin();
        //queue.erase(it);
        nodesTraversed++;
        cout << "Nodes traversed: " << nodesTraversed << endl;
        //cout << "Queue size:" << queue.size() << endl;
        //cout << nodesTraversed << endl;
        

        if(queueSize < queue.size()){
          queueSize = queue.size();
        }
        //  if problem.GOAL-TEST(node.STATE) succeeds then return node
        if(current->isGoal()){
          cout << "Heuristic: " << heuristic << endl;
          cout << "Depth: " << current->depth << endl;
          cout << "Nodes checked:" << nodesTraversed << endl;
          cout << "Max queue size: " << queueSize << endl;
          return current;
        }
        visited.push_back(current);
        //nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))
        searchWays(current);    
      }
    //if EMPTY(nodes) then return "failure"
    cout << "FAILURE" << endl;
    return nullptr;
  };  

  void searchWays(Node * input){
    
    vector<Node*> children = createChildren(input);
      for(int i = 0; i < children.size(); i++){ // putting the children in terms of decreasing fn
        int j = 0;
        //int queueFn = queue[j]->getFn();
        int childrenFn = children[i]->getFn();
        while(j < queue.size() && queue[j]->getFn() > childrenFn){
          j++;
        }
        vector<Node*>::iterator it = queue.begin() + j;
        queue.insert(it, children[i]);
      }
  }

    // 1 = UCS, 2 = Misplaced tiles, 3 = Manhattan distance
  int calculateHeuristic(vector<int>& trench) {
    if (heuristic == 1) {
      return 0;
    }
    int h = 0;
    for (int i = 0; i < 13; i++) {
        if (trench[i] == 0) {
            continue;
        }
        // misplaced tiles
        if (heuristic == 2) {
          if(i < 10){
            if (trench[i] != i+1){
              h++;
            }
          } else {
            if (trench[i] != 0){
              h++;
            }
          }
        // manhattan distance
        } else if (heuristic == 3) {
          int goalPos = trench[i] - 1;
          if(i < 10){
            h += abs(i - goalPos);
          } else {
            if(i == 10 && trench[i] != 0){
              h += (4 - goalPos); // because it's on top of 4th tile and index of the 4th is 3. +1 for making recess being extra
            } else if(i == 11 && trench[i] != 0){
              h += (6 - goalPos);
            } else if(i == 12 && trench[i] != 0){
              h += (8 - goalPos);
            }
          }
        }
    }
    return h;
  }


  //returns a vector of nodes (children of the input node)
  vector<Node*> createChildren(Node* input){
    vector<Node*> children;
    
    // Move from trench to empty trench positions (basically left and right)
    vector<int> emptyIndex = input->findEmpty();
    vector<int> emptyRecess = input->findEmptyRecess();

    vector<int> newTrench = input->getTrench();
    for (int j = 0; j < emptyIndex.size(); ++j) {
        int index = emptyIndex[j];
        if(index > 0 && newTrench[index-1] != 0){ // going left
          vector<int> temp = newTrench;
          swap(temp[index-1], temp[index]);
          Node* child = new Node(temp, input->getGn() + 1, calculateHeuristic(temp), input, input->getDepth()+1);
          children.push_back(child);
        } 
                
        if(index < 9 && newTrench[index+1] != 0){// going right
          vector<int> temp = newTrench;
          swap(temp[index+1], temp[index]);
          Node* child = new Node(temp, input->getGn() + 1, calculateHeuristic(temp), input, input->getDepth()+1);
          children.push_back(child);
        }
    }
    
    // Move from trench to recesses
    for (int i = 0; i < emptyRecess.size(); ++i) {
        int index = emptyRecess[i];
        if(index == 10 && newTrench[3] != 0){
          vector<int> temp = newTrench;
          swap(temp[10], temp[3]);
          Node* child = new Node(temp, input->getGn() + 1, calculateHeuristic(temp), input, input->getDepth()+1);
          children.push_back(child);
        }
        if(index == 11 && newTrench[5] != 0){
          vector<int> temp = newTrench;
          swap(temp[11], temp[5]);
          Node* child = new Node(temp, input->getGn() + 1, calculateHeuristic(temp), input, input->getDepth()+1);
          children.push_back(child);
        }
        if(index == 12 && newTrench[7] != 0){
          vector<int> temp = newTrench;
          swap(temp[12], temp[7]);
          Node* child = new Node(temp, input->getGn() + 1, calculateHeuristic(temp), input, input->getDepth()+1);
          children.push_back(child);
        }
    }
    
    // Move from recesses to trench
    for (int i = 0; i < emptyIndex.size(); ++i) {
        int index = emptyIndex[i];
        if(index == 3 && newTrench[10] != 0){
          vector<int> temp = newTrench;
          swap(temp[10], temp[3]);
          Node* child = new Node(temp, input->getGn() + 1, calculateHeuristic(temp), input, input->getDepth()+1);
          children.push_back(child);
        }
                
        if(index == 5 && newTrench[11] != 0){
          vector<int> temp = newTrench;
          swap(temp[11], temp[5]);
          Node* child = new Node(temp, input->getGn() + 1, calculateHeuristic(temp), input, input->getDepth()+1);
          children.push_back(child);
        }
        if(index == 7 && newTrench[12] != 0){
          vector<int> temp = newTrench;
            swap(temp[12], temp[7]);
            Node* child = new Node(temp, input->getGn() + 1, calculateHeuristic(temp), input, input->getDepth()+1);
            children.push_back(child);
        }
    }


    /*
    Moves we can do: 
    move a man into an adjacent empty space, move a man into an empty recess, move a man from recess into an adjacent empty space in trench
    can be observed as moving the empty tile within the trench or move it to recess or recess to trench

    */

  //checking for repeated children
  vector<Node*> children2;
    for(int i = 0; i < children.size(); i++ ){
      bool repeated = false;
        for(int j = 0; j < visited.size();j++){
          if(visited[j]->compareNodes(children[i])){
            repeated = true;
          }
        }
        if(repeated == false){
          children2.push_back(children[i]);
        }
    }
    return children2;
  }

};


#endif