#include <iostream>
#include <vector>

using namespace std;

class Node {
  public:
    int _grade;
    bool _visited = false;
    vector<Node*> _pointedTo;

    Node() {
      _grade = 0;

    }

    Node(int grade) {
        _grade = grade;
    }

    void addLine(Node *node) {
        _pointedTo.push_back(node);
    }

    void setGrade(int grade){
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

vector<Node*> processInput() {
  int nodes, paths, grade;
  int begin, end;
  char eater;

  cin >> nodes >> eater >> paths;

  vector<Node*> students(nodes);

  for(int i = 0; i < nodes; i++) {
    cin >> grade;

    Node *new_node = (Node *) malloc(sizeof(Node)); 
    
    *new_node = Node(grade);

    students.at(i) = new_node;
  }

  //for the paths
  for(int i = 0; i < paths; i++) {
    cin >> begin >> end;
    students.at(end - 1)->addLine(students.at(begin - 1));
  }

  return students;

}

//FEIO
Node* highestUnvisited(vector<Node*> students) {
  int pos = -1, grade = 0;

  for(int i = 0; i < (int) students.size(); i++) {
    if(students.at(i)->_grade > grade && !students.at(i)->_visited) {
      pos = i;
      grade = students.at(i)->_grade;
    }
  }

  if(pos == -1) return NULL;

  return students.at(pos);
}

int main() {

  //Tornar a merda dos students em ponteiros -> * <- this thing right here
  vector<Node*> students = processInput();

  Node *actual_node = highestUnvisited(students);

  while(true) {
    if(!actual_node) break;

    actual_node->spreadGrade(actual_node);

    actual_node = highestUnvisited(students);
  }

  for(int i = 0; i < (int) students.size(); i++) {
    printf("%d\n", students.at(i)->_grade);
  }

  return 0;

}