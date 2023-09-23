#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

/*

https://www.acmicpc.net/problem/16985


현재 문제가 있어서 특정 예제에서 제대로 동작 x

*/


// 층, 세로축(x), 가로축(y)
int board[5][5][5];
int tempBoard[5][5][5];
int visited[5][5][5];

// 오른쪽, 아래, 왼쪽, 위, 윗층, 아랫층
int dx[6] = { 0,1,0,-1,0,0 };
int dy[6] = { 1,0,-1,0,0,0 };
int dz[6] = { 0,0,0,0,-1,1 };


void bfs()
{
	queue<tuple<int, int, int>> q;

	q.push(make_tuple(0, 0, 0));
	visited[0][0][0] = 0;

	while (!q.empty())
	{
		tuple<int, int, int> currentXYZ = q.front();
		int nextVisitCount = visited[get<0>(currentXYZ)][get<1>(currentXYZ)][get<2>(currentXYZ)] + 1;
		q.pop();

		for (int i = 0; i < 6; i++)
		{
			int nextX = get<1>(currentXYZ) + dx[i];
			int nextY = get<2>(currentXYZ) + dy[i];
			int nextZ = get<0>(currentXYZ) + dz[i];


			if (nextX < 0 || nextY < 0 || nextZ < 0 || nextX >= 5 || nextY >= 5 || nextZ >= 5)
				continue;
			if (tempBoard[nextZ][nextX][nextY] == 0)
				continue;
			// 방문했었고, visited가 nextVisitCount보다 작거나 같으면 continue
			if (visited[nextZ][nextX][nextY] != -1 && visited[nextZ][nextX][nextY] <= nextVisitCount)
				continue;

			q.push(make_tuple(nextZ, nextX, nextY));
			visited[nextZ][nextX][nextY] = nextVisitCount;

		}
	}

}


// 시계 방향으로 1 => 90도 2=> 180 3=> 270 회전
void rotateBoard(int floor, int dir)
{
	if (dir == 0)
		return;
	int temp[5][5];

	for (int k = 0; k < dir; k++)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				temp[i][j] = tempBoard[floor][4 - j][i];
			}
		}
	}
	swap(tempBoard[floor], temp);
}


int main()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				cin >> board[i][j][k];
			}
		}
	}

	int sequence[5] = { 0,1,2,3,4 };
	int answer = INT_MAX;

	do {

		// board 세팅
		for (int i = 0; i < 1024; i++)
		{
			for (int t = 0; t < 5; t++)
			{
				// temp에 모든 층의 경우의수 (회전 제외)
				memcpy(tempBoard[t], board[sequence[t]], 25 * sizeof(int));
			}

			int temp = i;

			for (int j = 0; j < 5; j++)
			{
				int count = temp % 4;
				temp = temp / 4;
				rotateBoard(j, count);
			}


			if (tempBoard[0][0][0] == 0 || tempBoard[4][4][4] == 0)
				continue;

			for (int k = 0; k < 5; k++)
			{
				for (int t = 0; t < 5; t++)
				{
					fill(visited[k][t], visited[k][t] + 5, -1);
				}
			}

			bfs();

			if (visited[4][4][4] == -1)
				continue;
			if (answer == 12)
			{
				cout << answer;
				return 0;
			}

			if (visited[4][4][4] < answer)
			{
				answer = visited[4][4][4];
			}

		}


	} while (next_permutation(sequence, sequence + 5));

	if (answer == INT_MAX)
		cout << -1;
	else
		cout << answer;



}