#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

/*
	���� �ð��ʰ� �߻� ����ȭ �����ؾ���
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
		int stock = 0;

		int maxIdx = max_element(Day, Day + N) - Day;
		int maxValue = Day[maxIdx];

		for (int i = 0; i < N; i++)
		{
			if (i < maxIdx)
			{
				money -= Day[i];
				stock++;
			}
			else if (i == maxIdx)
			{
				money += stock * Day[i];
				stock = 0;

				maxIdx = max_element(Day + i + 1, Day + N) - Day;
				maxValue = Day[maxIdx];
			}

		}

		cout << money << "\n";



	}

}