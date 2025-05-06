#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <iostream>
#include <queue>
#include "node.h"
#include <vector>
#include <cmath> 

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


    //general_search(problem, QUEUEING-FUNCTION){
  Node* solve(Node* input){
    int nodes_traversed = 0;
    int max_queue_size = 0;

    //nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
      queue.push_back(input);

      //loop do 
      while(queue.size() > 0){
        // node = REMOVE-FRONT(nodes)  
        Node* current = queue.at(queue.size() - 1);
        queue.pop_back();
        
        nodes_traversed++;

        if(max_queue_size < queue.size()){
          max_queue_size = queue.size();
        }
        //  if problem.GOAL-TEST(node.STATE) succeeds then return node
        if(current->isGoal()){
          cout << "Heuristic: " << heuristic << endl;
          cout << "Depth: " << current->depth << endl;
          cout << "Nodes checked:" << nodes_traversed << endl;
          cout << "Max queue size: " << max_queue_size << endl;
          return current;
        }

        visited.push_back(current);
        //nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))
        search_ways(current);    
      }
      
    //if EMPTY(nodes) then return "failure"
    cout << "FAILURE" << endl;
    return nullptr;
  };  

  // 1 = UCS, 2 = MANHATTAN DISTANCE, 3 = MISPLACED TILES
  void search_ways(Node * input){
    
    vector<Node *> children = createChildren(input);
    //UCS
    if(heuristic == 1){ // h(n) is all 0 and cost to go to any path doesn't rly make much difference. 
      
    }

    //manhattan distance
    else if(heuristic == 2){
      for(int i = 0; i < children.size(); i++){

      }
    }

    //misplaced tile heuristic
    else{
      for(int i = 0; i < children.size(); i++){

      }
    }
  }


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

    vector<int> newTrench = input->trench;
    for (int j = 0; j < emptyIndex.size(); ++j) {
        int index = emptyIndex[j];
        if(newTrench[index-1] != 0 || index == 9){ // going left
            swap(newTrench[index-1], newTrench[index]);
            Node* neighbor = new Node(newTrench, input->gn + 1, calculateHeuristic(newTrench), input, input->getDepth()+1);
            children.push_back(neighbor);
        } 
                
        if(newTrench[index+1] != 0 || index == 0){// going right
            swap(newTrench[index+1], newTrench[index]);
            Node* neighbor = new Node(newTrench, input->gn + 1, calculateHeuristic(newTrench), input, input->getDepth()+1);
            children.push_back(neighbor);
        }
    }
    
    // Move from trench to recesses
    for (int i = 0; i < emptyRecess.size(); ++i) {
        int index = emptyRecess[i];
        if(index == 10 && newTrench[3] != 0){
            swap(newTrench[10], newTrench[3]);
            Node* neighbor = new Node(newTrench, input->gn + 1, calculateHeuristic(newTrench), input, input->getDepth()+1);
            children.push_back(neighbor);
        }
        if(index == 11 && newTrench[5] != 0){
            swap(newTrench[11], newTrench[5]);
            Node* neighbor = new Node(newTrench, input->gn + 1, calculateHeuristic(newTrench), input, input->getDepth()+1);
            children.push_back(neighbor);
        }
        if(index == 12 && newTrench[7] != 0){
            swap(newTrench[12], newTrench[7]);
            Node* neighbor = new Node(newTrench, input->gn + 1, calculateHeuristic(newTrench), input, input->getDepth()+1);
            children.push_back(neighbor);
        }

    }
    
    // Move from recesses to trench
    for (int i = 0; i < emptyIndex.size(); ++i) {
        int index = emptyIndex[i];
        if(index == 3 && newTrench[10] != 0){
            swap(newTrench[10], newTrench[3]);
            Node* neighbor = new Node(newTrench, input->gn + 1, calculateHeuristic(newTrench), input, input->getDepth()+1);
            children.push_back(neighbor);
        }
                
        if(index == 5 && newTrench[11] != 0){
            swap(newTrench[11], newTrench[5]);
            Node* neighbor = new Node(newTrench, input->gn + 1, calculateHeuristic(newTrench), input, input->getDepth()+1);
            children.push_back(neighbor);
        }
        if(index == 7 && newTrench[12] != 0){
            swap(newTrench[12], newTrench[7]);
            Node* neighbor = new Node(newTrench, input->gn + 1, calculateHeuristic(newTrench), input, input->getDepth()+1);
            children.push_back(neighbor);
        }
    }


    /*
    // Moves we can do: 
    // move a man into an adjacent empty space, move a man into an empty recess, move a man from recess into an adjacent empty space in trench
    // can be observed as moving the empty tile within the trench or move it to recess or recess to trench

    */

  //checking for repeated children
  vector<Node*> children2;
    for(int i = 0; i < children.size(); i++ ){
      bool repeated = false;
        for(int j = 0; j < visited.size();j++){
          if(visited[j]->compareNodes(*children[i])){
            repeated = true;
          }
        }
        if(repeated == false){
          children2.push_back(children.at(i));
        }
    }
    return children2;
  }

};


#endif