#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<queue>
#include<Windows.h>

using namespace std;

vector<vector<unsigned int>> graph;
vector<int> bfsNumber;

bool read(const string& path) {
	ifstream file(path);
	if (!file.is_open()) {
		cerr << "Файл графа не відкритий."
			<< "Помилка при відкритті файла."
			<< endl;
		return false;
	}
	
	graph.clear();
	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		unsigned int node;
		vector<unsigned int> neighbors;
		while (iss >> node)
			if (node > 0)
				neighbors.push_back(node - 1);
		graph.push_back(neighbors);
	}
	file.close();
	return true;
}

void print() {
	cout << "Суміжність вершин:" << endl;
	for (unsigned int i = 0; i < graph.size(); i++) {
		cout << "Вершина " << (i + 1) << ": {";
		for (unsigned int j = 0; j < graph[i].size(); j++) {
			cout << (graph[i][j] + 1);
			if (j < graph[i].size() - 1) {
				cout << ", ";
			}
		}
		cout << "}" << endl;
	}
}

void printBFSQueue(const queue<int>& q, int colWidth) {
	queue<int> temp = q;
	stringstream ss;
	ss << "[";
	bool first = true;
	while (!temp.empty()) {
		if (!first)
			ss << ", ";
		ss << (temp.front() + 1);
		temp.pop();
		first = false;
	}
	ss << "]";
	cout << left << setw(colWidth) << ss.str();
}

void printLine(int totalWidth) {
	cout << "+" << string(totalWidth - 2, '-') << "+" << endl;
}


void bfs(int start, const vector<vector<unsigned int >>& graph) {
vector<bool> isVisited(graph.size(), false);
    bfsNumber.clear();
    bfsNumber.resize(graph.size(), -1);
    queue<int> que;
    size_t bfsCount = 0;

    que.push(start);
    isVisited[start] = true;
    bfsNumber[start] = ++bfsCount;

    const int colWidth = 20;
    const int totalWidth = colWidth * 3 + 4;

    printLine(totalWidth);
    cout << "| " << left << setw(colWidth - 2) << "Поточна вершина"
         << " | " << setw(colWidth - 2) << "BFS-номер"
         << " | " << setw(colWidth - 2) << "Вміст черги" << " |" << endl;
    printLine(totalWidth);

    while (!que.empty()) {
        int curr = que.front();
        que.pop();
        cout << "| " << left << setw(colWidth - 2) << (curr + 1)
             << " | " << setw(colWidth - 2) << bfsNumber[curr]
             << " | ";
        printBFSQueue(que, colWidth - 2);
        cout << " |" << endl;
        printLine(totalWidth);

        for (int neighbor : graph[curr]) {
            if (neighbor >= 0 && neighbor < graph.size()) {  // Додана перевірка меж
                if (!isVisited[neighbor]) {
                    isVisited[neighbor] = true;
                    bfsNumber[neighbor] = ++bfsCount;
                    que.push(neighbor);
                }
            } else {
                cerr << "Сусід " << (neighbor + 1) << " виходить за межі графа!" << endl;
            }
        }
    }
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	string path;
	cout << "Введіть шлях для зчитування графа:";
	getline(cin, path);
	if (!read(path))
		return 1;
	print();
	unsigned int vertex;
	cout << "Введіть початкову вершину для обходу вшир: ";
	cin >> vertex;
	if (vertex < 1 || vertex > graph.size()) {
		cerr << "Вершина виходить за межі графа."
			<< endl;
		return 2;
	}
	cout << "Протокол обходу графа вшир:" << endl;
	bfs(vertex - 1, graph);
	return 0;
}