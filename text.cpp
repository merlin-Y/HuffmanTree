#include <iostream>
#include <cstring>
#include <queue>
 
using namespace std;
 
void Print(int a)
{
    cout << a << " ";
}
void DeepFirstTravel(int start, int** Tlist, int n, int visit[])
{
    Print(start);
    visit[start] = 1;
    for (int i = 0; i < n; i++)
    {
        if (Tlist[start][i] != 0 && visit[i] != 1)
            DeepFirstTravel(i, Tlist, n, visit);
    }
}
void BreadthFirstTravel(int start, int** Tlist, int n, int visit[])
{
    queue<int> q;
    Print(start);
    visit[start] = 1;
    q.push(start);
    int cur;
    while (!q.empty())
    {
        cur = q.front();
        q.pop();
        for (int i = 0; i < n; i++)
        {
            if (Tlist[cur][i] != 0 && visit[i] != 1)//先访问、标记，再入队
            {
                Print(i);
                visit[i] = 1;
                q.push(i);
            }
        }
    }
}
int main()
{
    int n;
    cin >> n;
    int** a;
    int* visit;
    a = new int* [n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
    }
    visit = new int[n];
    for (int i = 0; i < n; i++)
        visit[i] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    }
    cout << "DFS" << endl;
    for (int i = 0; i < n; i++)
    {
        DeepFirstTravel(i, a, n, visit);
        cout << endl;
        for (int i = 0; i < n; i++)
            visit[i] = 0;
 
    }
    cout << "WFS" << endl;
    for (int i = 0; i < n; i++)
    {
        BreadthFirstTravel(i, a, n, visit);
        cout << endl;
        for (int i = 0; i < n; i++)
            visit[i] = 0;
    }
}