#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

pair<int, int> flower[100005];

// ���� ���ư��� �ʹ� �˰����� �������� => �ܼ�ȭ�ؾ���

// true�� a�� �� ������
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

// a�� �� ���� �Ǿ
bool compare(pair<int, int> a, pair<int, int> b)
{
	if (a.first != b.first)
	{
		return isEarlyDay(a.first, b.first);
	}
	else
	{
		// �Ǵ� ���� ������ ���� ���� �ʴ� ���� ����
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

	// 3�� 1�� ���� �켭, ���� �ʰ� ���� �ָ� ã�ƾ���
	for (int i = 0; i < N; i++)
	{
		if (flower[i].first > 301)
		{
			break;
		}
		// lateDay�� �� ���� ����, true => lateDay�� �����ؾ���
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

	// 11�� 30�� ���Ŀ� ���鼭, ���� ������ �Ǵ� ��
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
		// ���õ� �ɺ��� �� �ʰ� �� => i�� ����ȵǴ� ����
		if (isEarlyDay(currentFade[2] * 100 + currentFade[3], flower[i].first))
		{
			if (earlyIdx == i)
			{
				answer = 0;
				break;
			}
			// ���� ������ ���¾� selectIdx ����
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

		// ������ ����Ǵ� �ֵ��߿� ���õ� �ֺ��� �� �ʰ� ���¾� ����
		if (isEarlyDay(flower[selectIdx].second, flower[i].second))
		{
			selectIdx = i;
		}

	}

	cout << answer;

}