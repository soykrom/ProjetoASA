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

    void changeVisited(Node *node, vector<Node*> &order) {
      node->_visited = true;

      for(int i = 0; i < (int) order.size(); i++) {
        if(order.at(i) == node) {
          order.erase(order.begin() + i);
          break;
        }
      }      
    }

    void spreadGrade(Node *node, vector<Node*> &order) {
      node->changeVisited(node, order);

      for(int i = 0; i < (int) node->_pointedTo.size(); i++) {
        if(!node->_pointedTo.at(i)->_visited) {
          node->_pointedTo.at(i)->setGrade(node->_grade);
          node->_pointedTo.at(i)->spreadGrade(node->_pointedTo.at(i), order);
        }
      }
      return;
    }
};

vector<Node*> processInput(vector<Node*> &order) {
  int nodes, paths, grade;
  int begin, end;
  char eater;

  cin >> nodes >> eater >> paths;

  Node *help = (Node *) malloc(sizeof(Node));  
  *help = Node();
  vector<Node*> students(nodes, help);
  order = students;

  for(int i = 0; i < nodes; i++) {
    int cont = 0;

    cin >> grade;

    Node *new_node = (Node *) malloc(sizeof(Node));   
    *new_node = Node(grade);

    students.at(i) = new_node;

    if(i != 0) {
      while(new_node->_grade < order.at(cont)->_grade) cont++;

      for(int aux = i; aux > cont; aux--) order.at(aux) = order.at(aux - 1);
    }

    order.at(cont) = new_node;

  }

  for(int i = 0; i < paths; i++) {
    cin >> begin >> end;
    students.at(end - 1)->addLine(students.at(begin - 1));
  }

  return students;
}


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
  vector<Node*> order;
  vector<Node*> students = processInput(order);

  Node *actual_node;

  while(true) {
    actual_node = order.at(0);


    actual_node->spreadGrade(actual_node, order);

    if(order.size() == 0) break;
  }

  for(int i = 0; i < (int) students.size(); i++) {
    printf("%d\n", students.at(i)->_grade);
    free(students.at(i));
  }



  return 0;

}

