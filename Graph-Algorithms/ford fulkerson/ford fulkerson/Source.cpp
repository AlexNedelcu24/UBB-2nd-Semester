#include <iostream>
#include <queue>
#include <string.h>
#include <fstream>
using namespace std;

ifstream in("f.in");
ofstream out("f.out");

#define maxim 10000
#define oo 1e9
int n, m;
int g[maxim][maxim],gr[maxim][maxim];
int parent[maxim];
int max_flow = 0;

bool bfs(int s, int t)
{

    bool visited[maxim];
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            if (visited[v] == false && gr[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

int Karp(int s, int t)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            gr[i][j] = g[i][j];


    while (bfs(s, t)) {
        int path_flow = oo;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, gr[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            gr[u][v] -= path_flow;
            gr[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main()
{
    in>>n>>m;
    for (int i = 1; i <= m; i++)
    {
        int x, y, c;
        in >> x >> y >> c;
        g[x][y] = c;
    }

    out<<Karp(0, n - 1);

    in.close();
    out.close();
}