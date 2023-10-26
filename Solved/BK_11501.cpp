#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

/*
	현재 시간초과 발생 최적화 진행해야함
*/

int Day[1000005];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	int N;

	cin >> T;

	while (T--)
	{

		cin >> N;
		for (int i = 0; i < N; i++)
		{
			cin >> Day[i];
		}
		long long money = 0;
		int current = Day[N - 1];
		for (int i = N - 1; i >= 0; i--)
		{
			if (current > Day[i])
			{
				money += current - Day[i];
			}
			else
			{
				current = Day[i];
			}
		}


		cout << money << "\n";



	}

}