#include <iostream>
#include <vector>

using namespace std;


vector<vector <int>> processInput(vector<int> &grades) {
    char trash;
    int nodes, lines;

    cin >> nodes >> trash >> lines;

    vector<vector <int>> matrix(nodes, vector <int>(nodes));

    grades.resize(nodes);
    for(int i = 0; i < nodes; i++) {
        cin >> grades[i];
    }

    int node, buddy;
    for(int i = 0; i < lines; i++) {
        cin >> node >> buddy;

        matrix[node - 1][buddy - 1] = 1;
    }

    return matrix;
}

int main() {
    vector<int> grades;

    vector<vector <int>> matrix = processInput(grades);
    

    

    for(int i = 0; i < grades.size(); i++) {
        cout << grades.at(i) << "\n";
    }

    return 0;
}