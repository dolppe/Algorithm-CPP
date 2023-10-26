#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

int V;
vector<pair<int, int>> tree[100005];
int visit[100005][2];
int answer[100005];

/*
백준 1167, bfs 돌려서 풀려고 했으나 반례가 존재함
*/

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> V;


	int min = 0;
	int startIdx = -1;
	for (int i = 1; i <= V; i++)
	{
		int temp;
		cin >> temp;
		int current = temp;
		cin >> temp;
		int count = 0;
		while (temp != -1)
		{
			int length;
			cin >> length;
			tree[current].push_back({ temp,length });
			count++;
			cin >> temp;
		}
		if (count != 0 && count > min)
		{
			startIdx = current;
			min = count;
		}

	}
	for (int i = 0; i <= V; i++)
		visit[i][0] = -1;
	queue<int> q;
	visit[startIdx][0] = 0;
	for (pair<int, int> next : tree[startIdx])
	{
		q.push(next.first);
		visit[next.first][0] = next.second;
		visit[next.first][1] = next.first;
	}

	while (!q.empty())
	{
		int current = q.front();
		int curLength = visit[current][0];
		int parent = visit[current][1];
		q.pop();

		for (pair<int, int> next : tree[current])
		{
			if (visit[next.first][0] != -1)
				continue;
			visit[next.first][0] = curLength + next.second;
			visit[next.first][1] = parent;
			q.push(next.first);
		}
	}


	for (int i = 1; i <= V; i++)
	{
		if (answer[visit[i][1]] < visit[i][0])
			answer[visit[i][1]] = visit[i][0];
	}

	int max1 = 0;
	int max2 = 0;
	for (pair<int, int> next : tree[startIdx])
	{
		if (answer[next.first] > max1)
		{
			max1 = answer[next.first];
			if (max2 < max1)
				swap(max1, max2);
		}

	}
	cout << max1 + max2;




}