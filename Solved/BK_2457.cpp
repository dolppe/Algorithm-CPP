#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

int N;
pair<int,int> days[100005];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++)
	{
		int stM, stD, enM, enD;
		cin >> stM >> stD >> enM >> enD;

		days[i] = { stM * 100 + stD,enM * 100 + enD };
	}

	sort(days, days+N);

	int selectFade = 301;
	int selectIdx = -1;
	int last = selectIdx;
	int count = 0;
	int i = 0;
	bool flag = false;
	while(true)
	{
		if (i == N)
		{
			if (last == selectIdx)
				flag = true;
			else
				if (days[selectIdx].second > 1130)
					count++;
				else
					flag = true;
			break;
		}
		if (days[i].first <= selectFade)
		{
			if (selectIdx == -1)
				selectIdx = i;
			else if (days[i].second > days[selectIdx].second)
				selectIdx = i;
			i++;
			continue;
		}
		else
		{
			// 꽃 선택 및 최신화
			if (last == selectIdx)
			{
				flag = true;
				break;
			}
			count++;
			selectFade = days[selectIdx].second;
			last = selectIdx;
			if (selectFade > 1130)
				break;
		}
	}
	if (flag)
		cout << 0;
	else
		cout << count;

}