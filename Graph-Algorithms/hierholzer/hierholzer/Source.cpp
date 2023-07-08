#include <iostream>
#include <stack>
#include <unordered_set>
#include <fstream>
#include <vector>

using namespace std;

ifstream in("f.in");
ofstream out("f.out");

#define MAX 10000

int V, E, PI[MAX];
unordered_set<int> ADJ[MAX];

void Hierholzer(int s, vector<int>& circuit) {
	stack<int> S;
	S.push(s);

	while (!S.empty()) {
		int u = S.top();
		if (ADJ[u].size() != 0) {
			int v = *ADJ[u].begin();
			ADJ[u].erase(v);
			ADJ[v].erase(u);
			S.push(v);
			continue;
		}
		S.pop();
		circuit.push_back(u);
	}
	circuit.pop_back();
}

int main() {

	in>>V>>E;
	for (int i = 0; i < E; ++i) {
		int x, y;
		in >> x >> y;
		ADJ[x].insert(y);
		ADJ[y].insert(x);
	}

	vector<int> euler;
	Hierholzer(0, euler);

	for (auto i : euler) {
		out << i << " ";
	}

	in.close();
	out.close();
}