#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

// 물건, 무게  => 가치
// D[i][j] i번째까지의 물건 선택, j 무게일때 가치
int D[100005][105];

// 무게, 가치
pair<int, int> bag[105];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int N, K;

	cin >> N >> K;

	for (int i = 1; i <= N; i++)
	{
		int w, v;
		cin >> w >> v;
		bag[i] = { w,v };

	}
	
	for (int i = 1; i <= K; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (i < bag[j].first)
				D[i][j] = D[i][j - 1];
			else
				D[i][j] = max(D[i][j - 1], bag[j].second + D[i - bag[j].first][j - 1]);

		}

	}
	cout << D[K][N];



}