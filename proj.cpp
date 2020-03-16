#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Node {
  public:
    int _grade;
    bool _visited = false;
    vector<Node*> _pointedTo;
    Node* _nextNode = NULL;

    Node() {
      _grade = 0;

    }

    Node(int grade) {
        _grade = grade;
    }

    void addLine(Node *node) {
        _pointedTo.push_back(node);
    }
 
    void setGrade(int grade) {
      _grade = grade;
    }

    void spreadGrade(Node *node) {
      node->_visited = true;
      for(int i = 0; i < (int) node->_pointedTo.size(); i++) {
        if(!node->_pointedTo.at(i)->_visited) {
          node->_pointedTo.at(i)->setGrade(node->_grade);
          node->_pointedTo.at(i)->spreadGrade(node->_pointedTo.at(i));
        }
      }

      return;
    }
};


Node** processInput(int &size) {
  int nodes, paths, grade;
  int begin, end;
  char eater;

  cin >> nodes >> eater >> paths;
  size = nodes;

  Node **students = new Node* [nodes];

  for(int i = 0; i < nodes; i++) {
    cin >> grade;

    Node *new_node = (Node *) malloc(sizeof(Node));

    *new_node = Node(grade);

    students[i] = new_node;

    if(i) students[i-1]->_nextNode = new_node;

  }

  //for the paths
  for(int i = 0; i < paths; i++) {
    cin >> begin >> end;
    students[end - 1]->addLine(students[begin - 1]);
  }

  return students;

}

Node* highestUnvisited(Node* students[], int size) {
  for(int i = 0; i < size; i++) {
    if(!students[i]->_visited)
      return students[i];
  }

  return NULL;
}

void heapify(Node* arr[], int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l]->_grade < arr[smallest]->_grade)
        smallest = l;

    if (r < n && arr[r]->_grade < arr[smallest]->_grade)
        smallest = r;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void heapSort(Node *arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}


int main() {
  int size;
  Node** students = processInput(size);
  Node* currentNode = students[0];

  heapSort(students, size);

  Node* highestNode;

  while(true) {
    highestNode = highestUnvisited(students, size);

    if(highestNode == NULL) break;

    highestNode->spreadGrade(highestNode);
  }

  while(true) {
    printf("%d\n", currentNode->_grade);

    currentNode = currentNode->_nextNode;

    if(currentNode == NULL) break;
  }

  return 0;
}
