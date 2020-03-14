#include <iostream>
#include <vector>

using namespace std;

class Node {
    public:
        int _grade;
        bool _visited = false;
        vector<Node> _pointedTo;

        Node(){}

        Node(int grade) {
            _grade = grade;
        }

        void addLine(Node node) {
            _pointedTo.push_back(node);
        }

        void setGrade(int grade){
          _grade = grade;
        }

        void spreadGrade(Node node) {
          node._visited = true;
          for(int i = 0; i < (int) node._pointedTo.size(); i++) {
              if(!node._pointedTo.at(i)._visited) {
                  node._pointedTo.at(i).setGrade(node._grade);
                  node._pointedTo.at(i).spreadGrade(_pointedTo.at(i));
              }
            }
          return;
        }

};

vector<Node> processInput(){
  int nodes, paths, grade;
  int begin, end;
  char eater;

  cin >> nodes >> eater >> paths;

  vector<Node> students(nodes);

  for(int i = 0; i < nodes; i++){
    cin >> grade;
    int cont = 0;
    while(grade < students.at(cont)._grade) {cont++; }
    for(int j = students.size() - 1; j > cont; j--) {
       students.at(j) = students.at(j - 1);
     }
     students.at(cont).setGrade(grade);
  }

  //for the paths
  for(int i = 0; i < paths; i++){
    cin >> begin >> end;
    students.at(end - 1).addLine(students.at(begin - 1));
  }


  return students;
}

int main(){

  //Tornar a merda dos students em ponteiros -> * <- this thing right here
  vector<Node> students = processInput();
  for(int i = 0; i < (int) students.size(); i++){
    if(!students.at(i)._visited){
      students.at(i).spreadGrade(students.at(i));
    }
  }

  for(int i = 0; i < (int) students.size(); i++){
    printf("%d\n", students.at(i)._grade);
  }

  return 0;

}
