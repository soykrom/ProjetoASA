#include <iostream>
#include <vector>

using namespace std;

class Node {
  public:
    int _grade;
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

    void setGrade(int grade) {
      _grade = grade;
    }

    void spreadGrade(Node *node) {
      for(int i = 0; i < (int) node->_pointedTo.size(); i++) {
        if(node->_pointedTo.at(i)->_grade >= node->_grade) continue;

        node->_pointedTo.at(i)->setGrade(node->_grade);
        node->_pointedTo.at(i)->spreadGrade(node->_pointedTo.at(i));
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

  for(int i = 0; i < paths; i++) {
    cin >> begin >> end;
    students.at(end - 1)->addLine(students.at(begin - 1));
  }

  return students;
}


int main() {
  vector<Node*> students = processInput();

  for(int i = 0; i < (int) students.size(); i++) {
    students.at(i)->spreadGrade(students.at(i));

  }

  for(int i = 0; i < (int) students.size(); i++) {
    printf("%d\n", students.at(i)->_grade);
    free(students.at(i));
  }

  return 0;

}