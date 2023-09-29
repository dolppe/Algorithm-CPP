#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

pair<int, int> flower[100005];

// 얼추 돌아가나 너무 알고리즘이 복잡해짐 => 단순화해야함

// true면 a가 더 일찍임
bool isEarlyDay(int a, int b)
{
	int aMonth, aDay, bMonth, bDay;
	aMonth = a / 100;
	aDay = a % 100;
	bMonth = b / 100;
	bDay = b % 100;
	if (aMonth != bMonth)
	{
		return aMonth < bMonth;
	}
	else
	{
		return aDay < bDay;
	}

}

// a가 더 빨리 피어남
bool compare(pair<int, int> a, pair<int, int> b)
{
	if (a.first != b.first)
	{
		return isEarlyDay(a.first, b.first);
	}
	else
	{
		// 피는 날이 같으면 지는 날이 늦는 쪽이 앞쪽
		return isEarlyDay(b.second, a.second);
	}
}




int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		int startMonth, startDay;
		int endMonth, endDay;

		cin >> startMonth >> startDay >> endMonth >> endDay;
		flower[i].first = startMonth * 100 + startDay;
		flower[i].second = endMonth * 100 + endDay;
	}

	sort(flower, flower + N, compare);

	int lateIdx = -1;
	int lateDay[4] = { -1,-1,-1,-1 };

	// 3월 1일 전에 펴서, 가장 늦게 지는 애를 찾아야함
	for (int i = 0; i < N; i++)
	{
		if (flower[i].first > 301)
		{
			break;
		}
		// lateDay가 더 빨리 지면, true => lateDay를 변경해야함
		if (isEarlyDay({ lateDay[2] * 100 + lateDay[3] }, flower[i].second))
		{
			lateDay[2] = flower[i].second / 100;
			lateDay[3] = flower[i].second % 100;
			lateIdx = i;
		}
	}
	if (lateIdx == -1)
	{
		cout << 0;
		return 0;
	}
	int earlyIdx = -1;
	int earlyDay[4] = { 12,12,12,12 };

	// 11월 30일 이후에 지면서, 가장 빠르게 피는 애
	for (int i = 0; i < N; i++)
	{
		if (flower[i].second / 100 != 12)
			continue;
		if (isEarlyDay(flower[i].first, earlyDay[0] * 100 + earlyDay[1]))
		{
			earlyDay[0] = flower[i].first / 100;
			earlyDay[1] = flower[i].first % 100;
			earlyIdx = i;
		}
	}
	if (earlyIdx == -1)
	{
		cout << 0;
		return 0;
	}

	int currentFade[4] = { -1,-1,-1,-1 };

	currentFade[2] = flower[lateIdx].second / 100;
	currentFade[3] = flower[lateIdx].second % 100;

	int selectIdx = lateIdx;
	int answer = 1;

	for (int i = lateIdx + 1; i < N; i++)
	{
		// 선택된 꽃보다 더 늦게 핌 => i는 연결안되는 상태
		if (isEarlyDay(currentFade[2] * 100 + currentFade[3], flower[i].first))
		{
			if (earlyIdx == i)
			{
				answer = 0;
				break;
			}
			// 가장 느리게 지는애 selectIdx 저장
			currentFade[2] = flower[selectIdx].second / 100;
			currentFade[3] = flower[selectIdx].second % 100;

			answer++;

			if (isEarlyDay(currentFade[2] * 100 + currentFade[3], flower[i].first))
			{
				answer = 0;
				break;
			}
		}
		if (earlyIdx == i)
		{
			answer++;
			break;
		}

		// 조건은 통과되는 애들중에 선택된 애보다 더 늦게 지는애 선택
		if (isEarlyDay(flower[selectIdx].second, flower[i].second))
		{
			selectIdx = i;
		}

	}

	cout << answer;

}